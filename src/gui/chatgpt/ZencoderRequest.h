#pragma once
#include "client/http/Request.h"
#include "common/String.h"

class ChatGPTModel;

/**
 * @brief ZencoderRequest class for handling message editing via Zencoder API
 */
class ZencoderRequest : public http::Request
{
public:
    /**
     * @brief Constructor for ZencoderRequest
     * 
     * @param chat_id The chat ID
     * @param message_id The message ID to edit
     * @param new_text The new text for the message
     * @param model Pointer to the ChatGPTModel
     */
    ZencoderRequest(String chat_id, String message_id, String new_text, ChatGPTModel* model);
    
    /**
     * @brief Handle API response
     * 
     * @param status HTTP status code
     * @param data Response data
     */
    void OnResponse(int status, ByteString data) override;
    
    /**
     * @brief Handle API connection errors
     * 
     * @param errorCode Error code
     */
    void OnError(int errorCode) override;
    
private:
    String chat_id_;      ///< Chat ID
    String message_id_;   ///< Message ID to edit
    String new_text_;     ///< New text for the message
    ChatGPTModel* model_; ///< Pointer to the ChatGPTModel
};#pragma once
#include "client/http/Request.h"
#include "common/String.h"

class ChatGPTModel;

/**
 * @brief ZencoderRequest class for handling message editing via Zencoder API
 */
class ZencoderRequest : public http::Request
{
public:
    /**
     * @brief Constructor for ZencoderRequest
     * 
     * @param chat_id The chat ID
     * @param message_id The message ID to edit
     * @param new_text The new text for the message
     * @param model Pointer to the ChatGPTModel
     */
    ZencoderRequest(String chat_id, String message_id, String new_text, ChatGPTModel* model);
    
    /**
     * @brief Handle API response
     * 
     * @param status HTTP status code
     * @param data Response data
     */
    void OnResponse(int status, ByteString data) override;
    
    /**
     * @brief Handle API connection errors
     * 
     * @param errorCode Error code
     */
    void OnError(int errorCode) override;
    
private:
    String chat_id_;      ///< Chat ID
    String message_id_;   ///< Message ID to edit
    String new_text_;     ///< New text for the message
    ChatGPTModel* model_; ///< Pointer to the ChatGPTModel
};#pragma once

#include "c:/Users/ACER/Documents/VISUAL PROJEKTY/powder/powder_toy/The-Powder-Toy/src/client/http/Request.h"
#include "c:/Users/ACER/Documents/VISUAL PROJEKTY/powder/powder_toy/The-Powder-Toy/src/gui/chatgpt/ChatGPTModel.h"
#include "c:/Users/ACER/Documents/VISUAL PROJEKTY/powder/powder_toy/The-Powder-Toy/src/common/String.h"

class ZencoderRequest : public http::Request
{
public:
    ZencoderRequest(String chat_id, String message_id, String new_text, ChatGPTModel* model);

private:
    String chat_id;
    String message_id;
    String new_text;
    ChatGPTModel* model;
};