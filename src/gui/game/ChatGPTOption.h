#pragma once
#include "QuickOption.h"

class GameController;

class ChatGPTOption: public QuickOption
{
    GameController * c;
public:
    ChatGPTOption(GameModel * m, GameController * c_);
    bool GetToggle() override;
    void perform() override;
};#pragma once
#include "QuickOption.h"

class GameController;

class ChatGPTOption: public QuickOption
{
    GameController * c;
public:
    ChatGPTOption(GameModel * m, GameController * c_);
    bool GetToggle() override;
    void perform() override;
};