#pragma once

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