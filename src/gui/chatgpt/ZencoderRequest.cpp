#include "ZencoderRequest.h"
#include "ChatGPTModel.h"
#include "prefs/GlobalPrefs.h"
#include "common/StringBuilder.h"
#include <thread>

/**
 * @brief Constructor for ZencoderRequest
 * 
 * @param chat_id The chat ID
 * @param message_id The message ID to edit
 * @param new_text The new text for the message
 * @param model Pointer to the ChatGPTModel
 */
ZencoderRequest::ZencoderRequest(String chat_id, String message_id, String new_text, ChatGPTModel* model) :
    http::Request("https://api.zencoder.ai/v1/chat/messages/" + message_id),
    chat_id_(chat_id),
    message_id_(message_id),
    new_text_(new_text),
    model_(model)
{
    // Get API key from preferences
    String apiKey = GlobalPrefs::Ref().Get("ChatGPT.APIKey", "");

    if (apiKey.empty())
    {
        // Use a default response if no API key is set
        model_->AddAssistantMessage("Please set your Zencoder API key in the preferences file.");
        model_->SetProcessing(false);
        return;
    }

    // Set up the request
    SetMethod(http::Request::Method::PUT);
    AddHeader("Content-Type", "application/json");
    AddHeader("Authorization", "Bearer " + apiKey);

    // Build the JSON payload
    StringBuilder json;
    json << "{";
    json << "\"chat_id\": \"" << chat_id_ << "\",";
    json << "\"message_id\": \"" << message_id_ << "\",";
    json << "\"new_text\": \"" << new_text_ << "\"";
    json << "}";

    // Set the request data
    SetPostData(json.Build().ToUtf8());
}

/**
 * @brief Handle API response
 * 
 * @param status HTTP status code
 * @param data Response data
 */
void ZencoderRequest::OnResponse(int status, ByteString data)
{
    if (status != 200)
    {
        model_->AddAssistantMessage("Error: Failed to get response from Zencoder API (Status " + String::Build(status) + ")");
        model_->SetProcessing(false);
        return;
    }

    // Simulate editing the message by adding a new message to the chat history
    model_->AddAssistantMessage("(Edited) " + new_text_);
    model_->SetProcessing(false);
}

/**
 * @brief Handle API connection errors
 * 
 * @param errorCode Error code
 */
void ZencoderRequest::OnError(int errorCode)
{
    model_->AddAssistantMessage("Error: Failed to connect to Zencoder API (Error " + String::Build(errorCode) + ")");
    model_->SetProcessing(false);
}#include "ZencoderRequest.h"
#include "ChatGPTModel.h"
#include "prefs/GlobalPrefs.h"
#include "common/StringBuilder.h"
#include <thread>

/**
 * @brief Constructor for ZencoderRequest
 * 
 * @param chat_id The chat ID
 * @param message_id The message ID to edit
 * @param new_text The new text for the message
 * @param model Pointer to the ChatGPTModel
 */
ZencoderRequest::ZencoderRequest(String chat_id, String message_id, String new_text, ChatGPTModel* model) :
    http::Request("https://api.zencoder.ai/v1/chat/messages/" + message_id),
    chat_id_(chat_id),
    message_id_(message_id),
    new_text_(new_text),
    model_(model)
{
    // Get API key from preferences
    String apiKey = GlobalPrefs::Ref().Get("ChatGPT.APIKey", "");

    if (apiKey.empty())
    {
        // Use a default response if no API key is set
        model_->AddAssistantMessage("Please set your Zencoder API key in the preferences file.");
        model_->SetProcessing(false);
        return;
    }

    // Set up the request
    SetMethod(http::Request::Method::PUT);
    AddHeader("Content-Type", "application/json");
    AddHeader("Authorization", "Bearer " + apiKey);

    // Build the JSON payload
    StringBuilder json;
    json << "{";
    json << "\"chat_id\": \"" << chat_id_ << "\",";
    json << "\"message_id\": \"" << message_id_ << "\",";
    json << "\"new_text\": \"" << new_text_ << "\"";
    json << "}";

    // Set the request data
    SetPostData(json.Build().ToUtf8());
}

/**
 * @brief Handle API response
 * 
 * @param status HTTP status code
 * @param data Response data
 */
void ZencoderRequest::OnResponse(int status, ByteString data)
{
    if (status != 200)
    {
        model_->AddAssistantMessage("Error: Failed to get response from Zencoder API (Status " + String::Build(status) + ")");
        model_->SetProcessing(false);
        return;
    }

    // Simulate editing the message by adding a new message to the chat history
    model_->AddAssistantMessage("(Edited) " + new_text_);
    model_->SetProcessing(false);
}

/**
 * @brief Handle API connection errors
 * 
 * @param errorCode Error code
 */
void ZencoderRequest::OnError(int errorCode)
{
    model_->AddAssistantMessage("Error: Failed to connect to Zencoder API (Error " + String::Build(errorCode) + ")");
    model_->SetProcessing(false);
}#include "ZencoderRequest.h"
#include "client/http/RequestManager.h"
#include "common/platform/Platform.h"
#include "prefs/GlobalPrefs.h"
#include "common/StringBuilder.h"
#include "json/json.h"

ZencoderRequest::ZencoderRequest(String chat_id, String message_id, String new_text, ChatGPTModel* model) :
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
}

void ZencoderRequest::OnResponse(int status, ByteString data)
{
    if (status != 200)
    {
        model->AddAssistantMessage("Error: Failed to get response from Zencoder API (Status " + String::Build(status) + ")");
        model->SetProcessing(false);
        return;
    }

    // Simulate editing the message by adding a new message to the chat history
    model->AddAssistantMessage("(Edited) " + new_text);
    model->SetProcessing(false);
}

void ZencoderRequest::OnError(int errorCode)
{
    model->AddAssistantMessage("Error: Failed to connect to Zencoder API (Error " + String::Build(errorCode) + ")");
    model->SetProcessing(false);
}