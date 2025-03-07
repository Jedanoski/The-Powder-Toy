#pragma once

#include "src/client/http/Request.h"
#include "src/gui/chatgpt/ChatGPTModel.h"
#include "src/common/String.h"

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