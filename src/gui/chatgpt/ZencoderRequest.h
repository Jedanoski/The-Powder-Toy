#pragma once

#pragma once

#include "client/http/Request.h"
#include "gui/chatgpt/ChatGPTModel.h"
#include "common/String.h"

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