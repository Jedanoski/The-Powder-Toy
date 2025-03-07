#include "ChatGPTView.h"
#include "ChatGPTController.h"
#include "ChatGPTModel.h"
#include "graphics/Graphics.h"
#include "gui/interface/Label.h"
#include "gui/interface/Textbox.h"
#include "gui/interface/Button.h"
#include "gui/interface/ScrollPanel.h"
#include "gui/interface/Engine.h"
#include "gui/Style.h"
#include "SimulationConfig.h"
#include <deque>
#include <SDL.h>

ChatGPTView::ChatGPTView():
    ui::Window(ui::Point(0, 0), ui::Point(WINDOWW, WINDOWH-50)),
    c(nullptr),
    doClose(false)
{
    // Create message input field
    messageInput = new ui::Textbox(ui::Point(10, Size.Y-40), ui::Point(Size.X-70, 30), "", "Type your message here...");
    messageInput->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
    messageInput->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
    messageInput->SetLimit(1024);
    AddComponent(messageInput);
    FocusComponent(messageInput);
    
    // Create send button
    sendButton = new ui::Button(ui::Point(Size.X-50, Size.Y-40), ui::Point(40, 30), "Send");
    sendButton->Appearance.HorizontalAlign = ui::Appearance::AlignCentre;
    sendButton->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
    sendButton->SetActionCallback({ [this] {
        if (messageInput->GetText().length() > 0) {
            c->SendMessage(messageInput->GetText());
            messageInput->SetText("");
        }
    }});
    AddComponent(sendButton);
    
    // Create messages panel
    messagesPanel = new ui::ScrollPanel(ui::Point(1, 1), ui::Point(Size.X-2, Size.Y-50));
    messagesPanel->SetBackgroundColour(ui::Colour(0, 0, 0, 0));
    AddComponent(messagesPanel);
    
    // Create processing indicator
    processingLabel = new ui::Label(ui::Point(10, Size.Y-60), ui::Point(Size.X-20, 16), "ChatGPT is thinking...");
    processingLabel->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
    processingLabel->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
    processingLabel->Appearance.TextColour = style::Colour::WarningTitle;
    processingLabel->Visible = false;
    AddComponent(processingLabel);
}

ChatGPTView::~ChatGPTView()
{
    for (auto label : messageLabels)
    {
        if (!label->GetParentWindow())
            delete label;
    }
}

void ChatGPTView::NotifyMessageChanged(ChatGPTModel * sender)
{
    // Clear existing message labels
    for (auto label : messageLabels)
    {
        messagesPanel->RemoveChild(label);
    }
    messageLabels.clear();
    
    // Add new message labels
    std::deque<ChatMessage> messages = sender->GetMessages();
    int currentY = 5;
    
    for (const auto& message : messages)
    {
        ui::Label* messageLabel = new ui::Label(ui::Point(10, currentY), ui::Point(messagesPanel->Size.X-40, -1), message.content);
        messageLabel->SetMultiline(true);
        messageLabel->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
        
        if (message.isUser)
        {
            messageLabel->Appearance.TextColour = ui::Colour(50, 230, 50);
        }
        else
        {
            messageLabel->Appearance.TextColour = ui::Colour(230, 230, 50);
        }
        
        messagesPanel->AddChild(messageLabel);
        messageLabels.push_back(messageLabel);

        // Add edit button
        AddEditButton(message.id, message.content);
        
        currentY += messageLabel->Size.Y + 10;
    }
    
    // Scroll to bottom
}

void ChatGPTView::AddEditButton(String message_id, String message_text)
{
    ui::Button* editButton = new ui::Button(ui::Point(messagesPanel->Size.X - 30, currentY), ui::Point(20, 20), "Edit");
    editButton->Appearance.HorizontalAlign = ui::Appearance::AlignCentre;
    editButton->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
    editButton->SetActionCallback({ [this, message_id, message_text] {
        // Create text input field
        ui::Textbox* editInput = new ui::Textbox(ui::Point(10, currentY + 30), ui::Point(messagesPanel->Size.X - 40, 30), message_text, "Edit your message here...");
        editInput->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
        editInput->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
        editInput->SetLimit(1024);
        messagesPanel->AddChild(editInput);

        // Create save button
        ui::Button* saveButton = new ui::Button(ui::Point(messagesPanel->Size.X - 80, currentY + 30), ui::Point(60, 30), "Save");
        saveButton->Appearance.HorizontalAlign = ui::Appearance::AlignCentre;
        saveButton->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
        saveButton->SetActionCallback({ [this, message_id, editInput, saveButton] {
            // Send the updated text to the Zencoder API
            c->EditMessage("chat_id", message_id, editInput->GetText());

            // Remove the text input field and save button
            messagesPanel->RemoveChild(editInput);
            messagesPanel->RemoveChild(saveButton);
            delete editInput;
            delete saveButton;
        }});
        messagesPanel->AddChild(saveButton);
    }});
    messagesPanel->AddChild(editButton);
    currentY += 60;
}
    
    // Scroll to bottom
    messagesPanel->SetScrollPosition(currentY);
}

void ChatGPTView::NotifyProcessingStateChanged(ChatGPTModel * sender)
{
    processingLabel->Visible = sender->IsProcessing();
    sendButton->Enabled = !sender->IsProcessing();
    messageInput->Enabled = !sender->IsProcessing();
}

void ChatGPTView::OnKeyPress(int key, int scan, bool repeat, bool shift, bool ctrl, bool alt)
{
    if (key == SDLK_ESCAPE || key == SDLK_AC_BACK)
    {
        if (!repeat)
            doClose = true;
        return;
    }
    
    if ((key == SDLK_RETURN || key == SDLK_KP_ENTER) && !repeat && messageInput->GetText().length() > 0 && !processingLabel->Visible)
    {
        c->SendMessage(messageInput->GetText());
        messageInput->SetText("");
        return;
    }
    
    Window::DoKeyPress(key, scan, repeat, shift, ctrl, alt);
}

void ChatGPTView::OnDraw()
{
    Graphics * g = GetGraphics();
    g->BlendFilledRect(RectSized(Position, Size), 0x000000_rgb.WithAlpha(180));
}

void ChatGPTView::OnTick()
{
    if (doClose)
    {
        c->Exit();
        doClose = false;
    }
}#include "ChatGPTView.h"
#include "ChatGPTController.h"
#include "ChatGPTModel.h"
#include "graphics/Graphics.h"
#include "gui/interface/Label.h"
#include "gui/interface/Textbox.h"
#include "gui/interface/Button.h"
#include "gui/interface/ScrollPanel.h"
#include "gui/interface/Engine.h"
#include "gui/Style.h"
#include "SimulationConfig.h"
#include <deque>
#include <SDL.h>

ChatGPTView::ChatGPTView():
    ui::Window(ui::Point(0, 0), ui::Point(WINDOWW, WINDOWH-50)),
    c(nullptr),
    doClose(false)
{
    // Create message input field
    messageInput = new ui::Textbox(ui::Point(10, Size.Y-40), ui::Point(Size.X-70, 30), "", "Type your message here...");
    messageInput->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
    messageInput->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
    messageInput->SetLimit(1024);
    AddComponent(messageInput);
    FocusComponent(messageInput);
    
    // Create send button
    sendButton = new ui::Button(ui::Point(Size.X-50, Size.Y-40), ui::Point(40, 30), "Send");
    sendButton->Appearance.HorizontalAlign = ui::Appearance::AlignCentre;
    sendButton->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
    sendButton->SetActionCallback({ [this] {
        if (messageInput->GetText().length() > 0) {
            c->SendMessage(messageInput->GetText());
            messageInput->SetText("");
        }
    }});
    AddComponent(sendButton);
    
    // Create messages panel
    messagesPanel = new ui::ScrollPanel(ui::Point(1, 1), ui::Point(Size.X-2, Size.Y-50));
    messagesPanel->SetBackgroundColour(ui::Colour(0, 0, 0, 0));
    AddComponent(messagesPanel);
    
    // Create processing indicator
    processingLabel = new ui::Label(ui::Point(10, Size.Y-60), ui::Point(Size.X-20, 16), "ChatGPT is thinking...");
    processingLabel->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
    processingLabel->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
    processingLabel->Appearance.TextColour = style::Colour::WarningTitle;
    processingLabel->Visible = false;
    AddComponent(processingLabel);
}

ChatGPTView::~ChatGPTView()
{
    for (auto label : messageLabels)
    {
        if (!label->GetParentWindow())
            delete label;
    }
}

void ChatGPTView::NotifyMessageChanged(ChatGPTModel * sender)
{
    // Clear existing message labels
    for (auto label : messageLabels)
    {
        messagesPanel->RemoveChild(label);
    }
    messageLabels.clear();
    
    // Add new message labels
    std::deque<ChatMessage> messages = sender->GetMessages();
    int currentY = 5;
    
    for (const auto& message : messages)
    {
        ui::Label* messageLabel = new ui::Label(ui::Point(10, currentY), ui::Point(messagesPanel->Size.X-40, -1), message.content);
        messageLabel->SetMultiline(true);
        messageLabel->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
        
        if (message.isUser)
        {
            messageLabel->Appearance.TextColour = ui::Colour(50, 230, 50);
        }
        else
        {
            messageLabel->Appearance.TextColour = ui::Colour(230, 230, 50);
        }
        
        messagesPanel->AddChild(messageLabel);
        messageLabels.push_back(messageLabel);
        
        currentY += messageLabel->Size.Y + 10;
    }
    
    // Scroll to bottom
    messagesPanel->SetScrollPosition(currentY);
}

void ChatGPTView::NotifyProcessingStateChanged(ChatGPTModel * sender)
{
    processingLabel->Visible = sender->IsProcessing();
    sendButton->Enabled = !sender->IsProcessing();
    messageInput->Enabled = !sender->IsProcessing();
}

void ChatGPTView::OnKeyPress(int key, int scan, bool repeat, bool shift, bool ctrl, bool alt)
{
    if (key == SDLK_ESCAPE || key == SDLK_AC_BACK)
    {
        if (!repeat)
            doClose = true;
        return;
    }
    
    if ((key == SDLK_RETURN || key == SDLK_KP_ENTER) && !repeat && messageInput->GetText().length() > 0 && !processingLabel->Visible)
    {
        c->SendMessage(messageInput->GetText());
        messageInput->SetText("");
        return;
    }
    
    Window::DoKeyPress(key, scan, repeat, shift, ctrl, alt);
}

void ChatGPTView::OnDraw()
{
    Graphics * g = GetGraphics();
    g->BlendFilledRect(RectSized(Position, Size), 0x000000_rgb.WithAlpha(180));
}

void ChatGPTView::OnTick()
{
    if (doClose)
    {
        c->Exit();
        doClose = false;
    }
}