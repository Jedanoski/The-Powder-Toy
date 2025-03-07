#pragma once

#include "client/http/Request.h"
#include "ChatGPTModel.h"
#include "common/String.h"

class ZencoderRequest : public http::Request
{
public:
    ZencoderRequest(String chat_id, String message_id, String new_text, ChatGPTModel* model);
    void OnResponse(int status, ByteString data) override;
    void OnError(int errorCode) override;

private:
    String chat_id;
    String message_id;
    String new_text;
    ChatGPTModel* model;
};