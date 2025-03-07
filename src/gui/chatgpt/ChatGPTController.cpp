#include "ChatGPTController.h"
#include "ChatGPTView.h"
#include "ChatGPTModel.h"
#include "gui/interface/Engine.h"
#include "client/http/Request.h"
#include "client/http/RequestManager.h"
#include "common/platform/Platform.h"
#include "prefs/GlobalPrefs.h"
#include <thread>
#include <chrono>
#include "common/StringBuilder.h"
#include "json/json.h"

class ZencoderRequest : public http::Request
{
public:
    ZencoderRequest(String chat_id, String message_id, String new_text, ChatGPTModel* model) :
        http::Request("https://api.zencoder.ai/v1/chat/messages/" + message_id),
        chat_id(chat_id),
        message_id(message_id),
        new_text(new_text),
        model(model)
    {
        // Get API key from preferences
        String apiKey = GlobalPrefs::Ref().Get("ChatGPT.APIKey", "");

        if (apiKey.empty())
        {
            // Use a default response if no API key is set
            model->AddAssistantMessage("Please set your Zencoder API key in the preferences file.");
            model->SetProcessing(false);
            return;
        }

        // Set up the request
        SetMethod(http::Request::Method::PUT);
        AddHeader("Content-Type", "application/json");
        AddHeader("Authorization", "Bearer " + apiKey);

        // Build the JSON payload
        StringBuilder json;
        json << "{";
        json << "\"chat_id\": \"" << chat_id << "\",";
        json << "\"message_id\": \"" << message_id << "\",";
        json << "\"new_text\": \"" << new_text << "\"";
        json << "}";

        // Set the request data
        SetPostData(json.Build().ToUtf8());

		std::thread([this]() {
			std::pair<int, ByteString> result = Finish();
			int status = result.first;
			ByteString data = result.second;

			if (status != 200)
			{
				model->AddAssistantMessage("Error: Failed to get response from Zencoder API (Status " + String::Build(status) + ")");
				model->SetProcessing(false);
				return;
			}

			// Simulate editing the message by adding a new message to the chat history
			model->AddAssistantMessage("(Edited) " + new_text);
			model->SetProcessing(false);
		}).detach();
    }

private:
    String chat_id;
    String message_id;
    String new_text;
    ChatGPTModel* model;
};

class ChatGPTRequest : public http::Request
{
public:
    ChatGPTRequest(String message, ChatGPTModel* model) :
        http::Request("https://api.openai.com/v1/chat/completions"),
        message(message),
        model(model)
    {
        // Get API key from preferences
        String apiKey = GlobalPrefs::Ref().Get("ChatGPT.APIKey", "");
        
        if (apiKey.empty())
        {
            // Use a default response if no API key is set
            std::thread([this]() {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                model->AddAssistantMessage("Please set your OpenAI API key in the preferences file. You can get an API key from https://platform.openai.com/api-keys");
                model->SetProcessing(false);
            }).detach();
            return;
        }
        
        // Set up the request
        AddHeader("Content-Type", "application/json");
        AddHeader("Authorization", "Bearer " + apiKey);
        
        // Build the JSON payload
        StringBuilder json;
        json << "{";
        json << "\"model\": \"gpt-3.5-turbo\",";
        json << "\"messages\": [";
        json << "{\"role\": \"system\", \"content\": \"You are a helpful assistant for The Powder Toy, a physics sandbox game. Provide concise and helpful responses.\"},";
        json << "{\"role\": \"user\", \"content\": \"" << EscapeJSON(message) << "\"}";
        json << "],";
        json << "\"temperature\": 0.7";
        json << "}";
        
        // Set the request data
        SetPostData(json.Build().ToUtf8());

		std::thread([this]() {
			std::pair<int, ByteString> result = Finish();
			int status = result.first;
			ByteString data = result.second;
        
			if (status != 200)
			{
				model->AddAssistantMessage("Error: Failed to get response from ChatGPT API (Status " + String::Build(status) + ")");
				model->SetProcessing(false);
				return;
			}
        
			try
			{
				// Parse the JSON response
				Json::Value root;
				Json::Reader reader;
				if (!reader.parse(data, root))
				{
					model->AddAssistantMessage("Error: Failed to parse response from ChatGPT API");
					model->SetProcessing(false);
					return;
				}
            
				// Extract the response text
				String responseText = root["choices"][0]["message"]["content"].asString().FromUtf8();
				model->AddAssistantMessage(responseText);
			}
			catch (std::exception& e)
			{
				model->AddAssistantMessage("Error: " + ByteString(e.what()).FromUtf8());
			}
        
			model->SetProcessing(false);
		}).detach();
    }
    
private:
    String message;
    ChatGPTModel* model;
    
    String EscapeJSON(String text)
    {
        StringBuilder escaped;
        for (size_t i = 0; i < text.length(); i++)
        {
            char32_t c = text[i];
            if (c == '\\' || c == '"')
            {
                escaped << '\\' << c;
            }
            else if (c == '\n')
            {
                escaped << "\\n";
            }
            else if (c == '\r')
            {
                escaped << "\\r";
            }
            else if (c == '\t')
            {
                escaped << "\\t";
            }
            else if (c < 32)
            {
                escaped << " ";
            }
            else
            {
                escaped << c;
            }
        }
        return escaped.Build();
    }
};

ChatGPTController::ChatGPTController(std::function<void ()> onDone_) :
    HasExited(false),
    onDone(onDone_)
{
    chatGPTModel = new ChatGPTModel();
    chatGPTView = new ChatGPTView();
    chatGPTView->AttachController(this);
    chatGPTModel->AddObserver(chatGPTView);
}

ChatGPTController::~ChatGPTController()
{
    delete chatGPTModel;
    chatGPTView->CloseActiveWindow();
    delete chatGPTView;
}

void ChatGPTController::SendMessage(String message)
{
    if (chatGPTModel->IsProcessing())
        return;
    
    chatGPTModel->AddUserMessage(message);
    chatGPTModel->SetProcessing(true);
    
    // Create and start the request
    auto request = std::make_unique<ChatGPTRequest>(message, chatGPTModel);
    request->Start();
}

void ChatGPTController::Exit()
{
    chatGPTView->CloseActiveWindow();
    if (onDone)
        onDone();
    HasExited = true;
}

ChatGPTView * ChatGPTController::GetView()
{
    return chatGPTView;
}

void ChatGPTController::EditMessage(String chat_id, String message_id, String new_text)
{
    if (chatGPTModel->IsProcessing())
        return;

    chatGPTModel->SetProcessing(true);

    // Create and start the request
    auto request = std::make_unique<ZencoderRequest>(chat_id, message_id, new_text, chatGPTModel);
    request->Start();
}
#include "ChatGPTView.h"
#include "ChatGPTModel.h"
#include "gui/interface/Engine.h"
#include "client/http/Request.h"
#include "client/http/RequestManager.h"
#include "common/platform/Platform.h"
#include "prefs/GlobalPrefs.h"
#include <thread>
#include <chrono>

class ChatGPTRequest : public http::Request
{
public:
    ChatGPTRequest(String message, ChatGPTModel* model) : 
        http::Request("https://api.openai.com/v1/chat/completions"),
        message(message),
        model(model)
    {
        // Get API key from preferences
        String apiKey = GlobalPrefs::Ref().Get("ChatGPT.APIKey", "");
        
        if (apiKey.empty())
        {
            // Use a default response if no API key is set
            std::thread([this]() {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                model->AddAssistantMessage("Please set your OpenAI API key in the preferences file. You can get an API key from https://platform.openai.com/api-keys");
                model->SetProcessing(false);
            }).detach();
            return;
        }
        
        // Set up the request
        AddHeader("Content-Type", "application/json");
        AddHeader("Authorization", "Bearer " + apiKey);
        
        // Build the JSON payload
        StringBuilder json;
        json << "{";
        json << "\"model\": \"gpt-3.5-turbo\",";
        json << "\"messages\": [";
        json << "{\"role\": \"system\", \"content\": \"You are a helpful assistant for The Powder Toy, a physics sandbox game. Provide concise and helpful responses.\"},";
        json << "{\"role\": \"user\", \"content\": \"" << EscapeJSON(message) << "\"}";
        json << "],";
        json << "\"temperature\": 0.7";
        json << "}";
        
        // Set the request data
        SetPostData(json.Build().ToUtf8());
    }
    
    void OnResponse(int status, ByteString data) override
    {
        if (status != 200)
        {
            model->AddAssistantMessage("Error: Failed to get response from ChatGPT API (Status " + String::Build(status) + ")");
            model->SetProcessing(false);
            return;
        }
        
        try
        {
            // Parse the JSON response
            Json::Value root;
            Json::Reader reader;
            if (!reader.parse(data, root))
            {
                model->AddAssistantMessage("Error: Failed to parse response from ChatGPT API");
                model->SetProcessing(false);
                return;
            }
            
            // Extract the response text
            String responseText = root["choices"][0]["message"]["content"].asString().FromUtf8();
            model->AddAssistantMessage(responseText);
        }
        catch (std::exception& e)
        {
            model->AddAssistantMessage("Error: " + ByteString(e.what()).FromUtf8());
        }
        
        model->SetProcessing(false);
    }
    
    void OnError(int errorCode) override
    {
        model->AddAssistantMessage("Error: Failed to connect to ChatGPT API (Error " + String::Build(errorCode) + ")");
        model->SetProcessing(false);
    }
    
private:
    String message;
    ChatGPTModel* model;
    
    String EscapeJSON(String text)
    {
        StringBuilder escaped;
        for (size_t i = 0; i < text.length(); i++)
        {
            char32_t c = text[i];
            if (c == '\\' || c == '"')
            {
                escaped << '\\' << c;
            }
            else if (c == '\n')
            {
                escaped << "\\n";
            }
            else if (c == '\r')
            {
                escaped << "\\r";
            }
            else if (c == '\t')
            {
                escaped << "\\t";
            }
            else if (c < 32)
            {
                escaped << " ";
            }
            else
            {
                escaped << c;
            }
        }
        return escaped.Build();
    }
};

ChatGPTController::ChatGPTController(std::function<void ()> onDone_) :
    HasExited(false),
    onDone(onDone_)
{
    chatGPTModel = new ChatGPTModel();
    chatGPTView = new ChatGPTView();
    chatGPTView->AttachController(this);
    chatGPTModel->AddObserver(chatGPTView);
}

ChatGPTController::~ChatGPTController()
{
    delete chatGPTModel;
    chatGPTView->CloseActiveWindow();
    delete chatGPTView;
}

void ChatGPTController::SendMessage(String message)
{
    if (chatGPTModel->IsProcessing())
        return;
    
    chatGPTModel->AddUserMessage(message);
    chatGPTModel->SetProcessing(true);
    
    // Create and start the request
    auto request = std::make_unique<ChatGPTRequest>(message, chatGPTModel);
    request->Start();
}

void ChatGPTController::Exit()
{
    chatGPTView->CloseActiveWindow();
    if (onDone)
        onDone();
    HasExited = true;
}

ChatGPTView * ChatGPTController::GetView()
{
    return chatGPTView;
}