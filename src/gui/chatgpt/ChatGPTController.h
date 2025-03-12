#pragma once
#include <functional>

class ChatGPTView;
class ChatGPTModel;
class String;

/**
 * @brief Controller class for the ChatGPT interface
 *
 * This class manages the communication between the view and model components
 * of the ChatGPT interface, and handles user interactions.
 */
class ChatGPTController
{
private:
    ChatGPTView* chatGPTView;    ///< Pointer to the view component
    ChatGPTModel* chatGPTModel;  ///< Pointer to the model component
    std::function<void()> onDone; ///< Callback function when controller is done

public:
    bool HasExited;  ///< Flag indicating if the controller has exited

    /**
     * @brief Constructor
     *
     * @param onDone_ Callback function to execute when controller is done
     */
    ChatGPTController(std::function<void()> onDone_ = nullptr);

    /**
     * @brief Destructor
     */
    ~ChatGPTController();

    /**
     * @brief Send a message to the ChatGPT API
     *
     * @param message The message to send
     */
    void SendMessage(String message);

    /**
     * @brief Edit a message via the Zencoder API
     *
     * @param chat_id The chat ID
     * @param message_id The message ID to edit
     * @param new_text The new text for the message
     */
    void EditMessage(String chat_id, String message_id, String new_text);

    /**
     * @brief Exit the ChatGPT interface
     */
    void Exit();

    /**
     * @brief Get the ChatGPTView object
     *
     * @return Pointer to the ChatGPTView
     */
    ChatGPTView* GetView();

    /**
     * @brief Get the ChatGPTModel object
     *
     * @return Pointer to the ChatGPTModel
     */
    ChatGPTModel* GetModel() { return chatGPTModel; }
};