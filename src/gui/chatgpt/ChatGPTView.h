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

/**
 * @brief View class for the ChatGPT interface
 *
 * This class manages the user interface for the ChatGPT feature.
 * It displays messages and handles user input.
 */
class ChatGPTView : public ui::Window
{
private:
    ChatGPTController* c;                   ///< Pointer to the controller
    ui::Textbox* messageInput;              ///< Text input for user messages
    ui::Button* sendButton;                 ///< Button to send messages
    ui::ScrollPanel* messagesPanel;         ///< Panel to display messages
    std::vector<ui::Label*> messageLabels;  ///< Labels for displaying messages
    ui::Label* processingLabel;             ///< Label to show processing status
    bool doClose;                           ///< Flag to close the window

public:
    /**
     * @brief Constructor
     */
    ChatGPTView();

    /**
     * @brief Destructor
     */
    virtual ~ChatGPTView();

    /**
     * @brief Attach a controller to this view
     *
     * @param c_ Pointer to the controller
     */
    void AttachController(ChatGPTController* c_) { c = c_; }

    /**
     * @brief Handle notification that messages have changed
     *
     * @param sender Pointer to the model that sent the notification
     */
    void NotifyMessageChanged(ChatGPTModel* sender);

    /**
     * @brief Handle notification that processing state has changed
     *
     * @param sender Pointer to the model that sent the notification
     */
    void NotifyProcessingStateChanged(ChatGPTModel* sender);

    /**
     * @brief Draw the view
     */
    void OnDraw() override;

    /**
     * @brief Handle tick events
     */
    void OnTick() override;

    /**
     * @brief Handle key press events
     *
     * @param key Key code
     * @param scan Scan code
     * @param repeat Whether the key is being held down
     * @param shift Whether shift is pressed
     * @param ctrl Whether ctrl is pressed
     * @param alt Whether alt is pressed
     */
    void OnKeyPress(int key, int scan, bool repeat, bool shift, bool ctrl, bool alt) override;
};