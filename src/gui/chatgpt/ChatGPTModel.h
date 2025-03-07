#pragma once
#include "common/String.h"
#include <vector>
#include <deque>

class ChatGPTView;

struct ChatMessage
{
    String content;
    bool isUser;
    String id;
    
    ChatMessage(String content_, bool isUser_, String id_) : content(content_), isUser(isUser_), id(id_) {}
};

class ChatGPTModel
{
private:
    std::vector<ChatGPTView*> observers;
    std::deque<ChatMessage> messages;
    bool isProcessing;
    
    void notifyMessageChanged();
    void notifyProcessingStateChanged();
    
public:
    ChatGPTModel();
    ~ChatGPTModel();
    
    void AddObserver(ChatGPTView * observer);
    void AddUserMessage(String message);
    void AddAssistantMessage(String message);
    void SetProcessing(bool processing);
    bool IsProcessing() const { return isProcessing; }
    std::deque<ChatMessage> GetMessages() const { return messages; }
};#pragma once
#include "common/String.h"
#include <vector>
#include <deque>

class ChatGPTView;

struct ChatMessage
{
    String content;
    bool isUser;
    
    ChatMessage(String content_, bool isUser_) : content(content_), isUser(isUser_) {}
};

class ChatGPTModel
{
private:
    std::vector<ChatGPTView*> observers;
    std::deque<ChatMessage> messages;
    bool isProcessing;
    
    void notifyMessageChanged();
    void notifyProcessingStateChanged();
    
public:
    ChatGPTModel();
    ~ChatGPTModel();
    
    void AddObserver(ChatGPTView * observer);
    void AddUserMessage(String message);
    void AddAssistantMessage(String message);
    void SetProcessing(bool processing);
    bool IsProcessing() const { return isProcessing; }
    std::deque<ChatMessage> GetMessages() const { return messages; }
};