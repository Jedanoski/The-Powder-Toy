#include "ChatGPTOption.h"
#include "GameModel.h"
#include "GameController.h"
#include "gui/chatgpt/ChatGPTController.h"

ChatGPTOption::ChatGPTOption(GameModel * m, GameController * c_):
    QuickOption("A", "Open ChatGPT Assistant \bg(Ctrl+A)", m, Toggle)
{
    c = c_;
}

bool ChatGPTOption::GetToggle()
{
    return false;
}

void ChatGPTOption::perform()
{
    c->OpenChatGPT();
}#include "ChatGPTOption.h"
#include "GameModel.h"
#include "GameController.h"
#include "gui/chatgpt/ChatGPTController.h"

ChatGPTOption::ChatGPTOption(GameModel * m, GameController * c_):
    QuickOption("A", "Open ChatGPT Assistant \bg(Ctrl+A)", m, Toggle)
{
    c = c_;
}

bool ChatGPTOption::GetToggle()
{
    return false;
}

void ChatGPTOption::perform()
{
    c->OpenChatGPT();
}