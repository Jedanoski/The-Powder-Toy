#pragma once
#include "client/http/Request.h"
#include "common/String.h"

class ChatGPTModel;

/**
 * @brief ChatGPTRequest class for handling API requests to ChatGPT
 */
class ChatGPTRequest : public http::Request
{
public:
    /**
     * @brief Constructor for ChatGPTRequest
     * 
     * @param message The message to send to ChatGPT
     * @param model Pointer to the ChatGPTModel
     */
    ChatGPTRequest(String message, ChatGPTModel* model);
    
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
    String message_;     ///< Message to send to ChatGPT
    ChatGPTModel* model_; ///< Pointer to the ChatGPTModel
};