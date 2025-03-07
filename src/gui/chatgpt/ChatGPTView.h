#pragma once
#include "gui/interface/Window.h"
#include "common/String.h"
#include <vector>

class ChatGPTController;
class ChatGPTModel;
namespace ui
{
    class Textbox;
    class Button;
    class Label;
    class ScrollPanel;
}

class ChatGPTView : public ui::Window
{
private:
    ChatGPTController * c;
    ui::Textbox * messageInput;
    ui::Button * sendButton;
    ui::ScrollPanel * messagesPanel;
    std::vector<ui::Label*> messageLabels;
    ui::Label * processingLabel;
    bool doClose;

public:
    ChatGPTView();
    virtual ~ChatGPTView();
    
    void AttachController(ChatGPTController * c_) { c = c_; }
    void NotifyMessageChanged(ChatGPTModel * sender);
    void NotifyProcessingStateChanged(ChatGPTModel * sender);
    
    void AddEditButton(String message_id, String message_text);

    void OnDraw() override;
    void OnTick() override;
    void OnKeyPress(int key, int scan, bool repeat, bool shift, bool ctrl, bool alt) override;
};#pragma once
#include "gui/interface/Window.h"
#include "common/String.h"
#include <vector>

class ChatGPTController;
class ChatGPTModel;
namespace ui
{
    class Textbox;
    class Button;
    class Label;
    class ScrollPanel;
}

class ChatGPTView : public ui::Window
{
private:
    ChatGPTController * c;
    ui::Textbox * messageInput;
    ui::Button * sendButton;
    ui::ScrollPanel * messagesPanel;
    std::vector<ui::Label*> messageLabels;
    ui::Label * processingLabel;
    bool doClose;

public:
    ChatGPTView();
    virtual ~ChatGPTView();
    
    void AttachController(ChatGPTController * c_) { c = c_; }
    void NotifyMessageChanged(ChatGPTModel * sender);
    void NotifyProcessingStateChanged(ChatGPTModel * sender);
    
    void OnDraw() override;
    void OnTick() override;
    void OnKeyPress(int key, int scan, bool repeat, bool shift, bool ctrl, bool alt) override;
};