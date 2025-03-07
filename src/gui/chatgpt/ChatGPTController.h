#pragma once
#include <functional>

class ChatGPTView;
class ChatGPTModel;

class ChatGPTController
{
private:
    ChatGPTView * chatGPTView;
    ChatGPTModel * chatGPTModel;
    std::function<void ()> onDone;

public:
    bool HasExited;
    ChatGPTController(std::function<void ()> onDone_ = nullptr);
    ~ChatGPTController();
    
    void SendMessage(String message);
    void Exit();
    ChatGPTView * GetView();
};#pragma once
#include <functional>

class ChatGPTView;
class ChatGPTModel;

class ChatGPTController
{
private:
    ChatGPTView * chatGPTView;
    ChatGPTModel * chatGPTModel;
    std::function<void ()> onDone;

public:
    bool HasExited;
    ChatGPTController(std::function<void ()> onDone_ = nullptr);
    ~ChatGPTController();
    
    void SendMessage(String message);
    void EditMessage(String chat_id, String message_id, String new_text);
    void Exit();
    ChatGPTView * GetView();
};