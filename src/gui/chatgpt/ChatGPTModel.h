#pragma once
#include "common/String.h"
#include <vector>
#include <deque>

class ChatGPTView;

/**
 * @brief Structure to represent a chat message
 */
struct ChatMessage
{
    String content;  ///< Message content
    bool isUser;     ///< Flag indicating if the message is from the user
    String id;       ///< Unique identifier for the message

    /**
     * @brief Constructor for ChatMessage
     *
     * @param content_ Message content
     * @param isUser_ Flag indicating if the message is from the user
     * @param id_ Unique identifier for the message
     */
    ChatMessage(String content_, bool isUser_, String id_ = "") : content(content_), isUser(isUser_), id(id_) {}
};

/**
 * @brief Model class for the ChatGPT interface
 *
 * This class manages the data and business logic for the ChatGPT interface.
 * It follows the Observer pattern to notify views of changes.
 */
class ChatGPTModel
{
private:
    std::vector<ChatGPTView*> observers;  ///< List of observers to notify of changes
    std::deque<ChatMessage> messages;     ///< Queue of chat messages
    bool isProcessing;                    ///< Flag indicating if a request is being processed
    int nextMessageId;                    ///< Next message ID to assign

    /**
     * @brief Notify observers that messages have changed
     */
    void notifyMessageChanged();

    /**
     * @brief Notify observers that processing state has changed
     */
    void notifyProcessingStateChanged();

public:
    /**
     * @brief Constructor
     */
    ChatGPTModel();

    /**
     * @brief Destructor
     */
    ~ChatGPTModel();

    /**
     * @brief Add an observer to be notified of changes
     *
     * @param observer Pointer to the observer
     */
    void AddObserver(ChatGPTView* observer);

    /**
     * @brief Add a user message to the chat
     *
     * @param message The message to add
     */
    void AddUserMessage(String message);

    /**
     * @brief Add an assistant message to the chat
     *
     * @param message The message to add
     */
    void AddAssistantMessage(String message);

    /**
     * @brief Set the processing state
     *
     * @param processing The new processing state
     */
    void SetProcessing(bool processing);

    /**
     * @brief Check if a request is being processed
     *
     * @return True if processing, false otherwise
     */
    bool IsProcessing() const { return isProcessing; }

    /**
     * @brief Get all chat messages
     *
     * @return Queue of chat messages
     */
    std::deque<ChatMessage> GetMessages() const { return messages; }
};