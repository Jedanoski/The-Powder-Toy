#include "ChatGPTModel.h"
#include "ChatGPTView.h"
#include "prefs/GlobalPrefs.h"

ChatGPTModel::ChatGPTModel() : isProcessing(false), nextMessageId(0)
{
    // Load previous chat history from preferences
    std::vector<String> chatHistory = GlobalPrefs::Ref().Get("ChatGPT.History", std::vector<String>{});
    std::vector<bool> chatIsUser = GlobalPrefs::Ref().Get("ChatGPT.IsUser", std::vector<bool>{});
    
    // Ensure both vectors have the same size
    size_t minSize = std::min(chatHistory.size(), chatIsUser.size());
    
    for (size_t i = 0; i < minSize; i++)
    {
        messages.push_back(ChatMessage(chatHistory[i], chatIsUser[i], ""));
    }
    
    // If no history, add a welcome message
    if (messages.empty())
    {
        AddAssistantMessage("Hello! I'm your ChatGPT assistant for The Powder Toy. How can I help you today?");
    }
}

ChatGPTModel::~ChatGPTModel()
{
    // Save chat history to preferences
    std::vector<String> chatHistory;
    std::vector<bool> chatIsUser;
    
    for (const auto& message : messages)
    {
        chatHistory.push_back(message.content);
        chatIsUser.push_back(message.isUser);
    }
    
    // Limit history to last 50 messages
    if (chatHistory.size() > 50)
    {
        chatHistory.erase(chatHistory.begin(), chatHistory.begin() + (chatHistory.size() - 50));
        chatIsUser.erase(chatIsUser.begin(), chatIsUser.begin() + (chatIsUser.size() - 50));
    }
    
    GlobalPrefs::Ref().Set("ChatGPT.History", chatHistory);
    GlobalPrefs::Ref().Set("ChatGPT.IsUser", chatIsUser);
}

void ChatGPTModel::AddObserver(ChatGPTView * observer)
{
    observers.push_back(observer);
    observer->NotifyMessageChanged(this);
}

void ChatGPTModel::AddUserMessage(String message)
{
    String id = String::Build(nextMessageId++);
    messages.push_back(ChatMessage(message, true, id));
    notifyMessageChanged();
}

void ChatGPTModel::AddAssistantMessage(String message)
{
    String id = String::Build(nextMessageId++);
    messages.push_back(ChatMessage(message, false, id));
    notifyMessageChanged();
}

void ChatGPTModel::SetProcessing(bool processing)
{
    isProcessing = processing;
    notifyProcessingStateChanged();
}

void ChatGPTModel::notifyMessageChanged()
{
    for (size_t i = 0; i < observers.size(); i++)
    {
        observers[i]->NotifyMessageChanged(this);
    }
}

void ChatGPTModel::notifyProcessingStateChanged()
{
    for (size_t i = 0; i < observers.size(); i++)
    {
        observers[i]->NotifyProcessingStateChanged(this);
    }
}