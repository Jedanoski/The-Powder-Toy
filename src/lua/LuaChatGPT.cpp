#include "LuaChatGPT.h"
#include "gui/game/GameController.h"
#include "gui/chatgpt/ChatGPTController.h"
#include "gui/chatgpt/ChatGPTModel.h"
#include "gui/chatgpt/ChatGPTView.h"
#include "client/http/Request.h"
#include "client/http/RequestManager.h"
#include "common/platform/Platform.h"
#include <thread>
#include <chrono>

/**
 * @brief Open the ChatGPT interface from Lua
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int open(lua_State *L)
{
    auto *lsi = GetLSI();
    lsi->gameController->OpenChatGPT();
    return 0;
}

/**
 * @brief Send a message to ChatGPT from Lua
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int sendMessage(lua_State *L)
{
    auto *lsi = GetLSI();
    String message = tpt_lua_checkString(L, 1);
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lsi->gameController->OpenChatGPT();
        chatGPT = lsi->gameController->GetChatGPTController();
    }
    
    if (chatGPT)
    {
        chatGPT->SendMessage(message);
        lua_pushboolean(L, true);
    }
    else
    {
        lua_pushboolean(L, false);
    }
    
    return 1;
}

/**
 * @brief Get the last response from ChatGPT
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int getLastResponse(lua_State *L)
{
    auto *lsi = GetLSI();
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lua_pushnil(L);
        return 1;
    }
    
    auto *model = chatGPT->GetModel();
    if (!model)
    {
        lua_pushnil(L);
        return 1;
    }
    
    auto messages = model->GetMessages();
    if (messages.empty())
    {
        lua_pushnil(L);
        return 1;
    }
    
    // Find the last assistant message
    for (auto it = messages.rbegin(); it != messages.rend(); ++it)
    {
        if (!it->isUser)
        {
            tpt_lua_pushString(L, it->content);
            return 1;
        }
    }
    
    lua_pushnil(L);
    return 1;
}

/**
 * @brief Search the web for information related to a query
 *
 * @param L Lua state
 * @return Number of return values
 */
static int searchWeb(lua_State *L)
{
    auto *lsi = GetLSI();
    String query = tpt_lua_checkString(L, 1);

    // Create a new table to store the search results
    lua_newtable(L);

    // Perform the web search
    try
    {
        // This is a placeholder for actual web search implementation
        // In a real implementation, you would call an external API or service

        // Simulate search results
        lua_pushinteger(L, 1);
        lua_pushstring(L, "The Powder Toy is a free physics sandbox game.");
        lua_settable(L, -3);

        lua_pushinteger(L, 2);
        lua_pushstring(L, "It simulates air pressure, velocity, heat, gravity and many interactions.");
        lua_settable(L, -3);

        lua_pushinteger(L, 3);
        lua_pushstring(L, "You can create complex machines, guns, bombs, and more.");
        lua_settable(L, -3);
    }
    catch (std::exception &e)
    {
        lua_pop(L, 1); // Remove the table
        lua_pushnil(L);
        lua_pushstring(L, e.what());
        return 2;
    }

    return 1;
}

/**
 * @brief Generate Powder Toy code from a description
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int generateCode(lua_State *L)
{
    auto *lsi = GetLSI();
    String description = tpt_lua_checkString(L, 1);
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lsi->gameController->OpenChatGPT();
        chatGPT = lsi->gameController->GetChatGPTController();
    }
    
    if (chatGPT)
    {
        // Prepare a prompt for code generation
        String prompt = "Generate Powder Toy code for: " + description + "\nPlease provide only the code without explanations.";
        
        // Send the message to ChatGPT
        chatGPT->SendMessage(prompt);
        
        // Wait for the response (this is a simplified approach)
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Get the response
        auto *model = chatGPT->GetModel();
        if (model)
        {
            auto messages = model->GetMessages();
            if (!messages.empty())
            {
                // Find the last assistant message
                for (auto it = messages.rbegin(); it != messages.rend(); ++it)
                {
                    if (!it->isUser)
                    {
                        tpt_lua_pushString(L, it->content);
                        return 1;
                    }
                }
            }
        }
    }
    
    lua_pushnil(L);
    return 1;
}

/**
 * @brief Learn from a conversation topic
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int learnTopic(lua_State *L)
{
    auto *lsi = GetLSI();
    String topic = tpt_lua_checkString(L, 1);
    
    // This is a placeholder for actual learning implementation
    // In a real implementation, you would store the topic and use it to improve responses
    
    lua_pushboolean(L, true);
    return 1;
}

void LuaChatGPT::Open(lua_State *L)
{
    static const luaL_Reg reg[] = {
        {"open", open},
        {"sendMessage", sendMessage},
        {"getLastResponse", getLastResponse},
        {"searchWeb", searchWeb},
        {"generateCode", generateCode},
        {"learnTopic", learnTopic},
        {nullptr, nullptr}
    };
    
    lua_newtable(L);
    luaL_register(L, nullptr, reg);
    lua_setglobal(L, "chatgpt");
}#include "LuaChatGPT.h"
#include "gui/game/GameController.h"
#include "gui/chatgpt/ChatGPTController.h"
#include "gui/chatgpt/ChatGPTModel.h"
#include "gui/chatgpt/ChatGPTView.h"
#include "client/http/Request.h"
#include "client/http/RequestManager.h"
#include "common/platform/Platform.h"
#include <thread>
#include <chrono>
#include "web_search.h"

/**
 * @brief Open the ChatGPT interface from Lua
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int open(lua_State *L)
{
    auto *lsi = GetLSI();
    lsi->gameController->OpenChatGPT();
    return 0;
}

/**
 * @brief Send a message to ChatGPT from Lua
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int sendMessage(lua_State *L)
{
    auto *lsi = GetLSI();
    String message = tpt_lua_checkString(L, 1);
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lsi->gameController->OpenChatGPT();
        chatGPT = lsi->gameController->GetChatGPTController();
    }
    
    if (chatGPT)
    {
        chatGPT->SendMessage(message);
        lua_pushboolean(L, true);
    }
    else
    {
        lua_pushboolean(L, false);
    }
    
    return 1;
}

/**
 * @brief Get the last response from ChatGPT
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int getLastResponse(lua_State *L)
{
    auto *lsi = GetLSI();
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lua_pushnil(L);
        return 1;
    }
    
    auto *model = chatGPT->GetModel();
    if (!model)
    {
        lua_pushnil(L);
        return 1;
    }
    
    auto messages = model->GetMessages();
    if (messages.empty())
    {
        lua_pushnil(L);
        return 1;
    }
    
    // Find the last assistant message
    for (auto it = messages.rbegin(); it != messages.rend(); ++it)
    {
        if (!it->isUser)
        {
            tpt_lua_pushString(L, it->content);
            return 1;
        }
    }
    
    lua_pushnil(L);
    return 1;
}

/**
 * @brief Search the web for information related to a query
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int searchWeb(lua_State *L)
{
    auto *lsi = GetLSI();
    String query = tpt_lua_checkString(L, 1);
    
    // Create a new table to store the search results
    lua_newtable(L);
    
    // Perform the web search
    try
    {
        // This is a placeholder for actual web search implementation
        // In a real implementation, you would call an external API or service
        
        // Simulate search results
        lua_pushinteger(L, 1);
        lua_pushstring(L, "The Powder Toy is a free physics sandbox game.");
        lua_settable(L, -3);
        
        lua_pushinteger(L, 2);
        lua_pushstring(L, "It simulates air pressure, velocity, heat, gravity and many interactions.");
        lua_settable(L, -3);
        
        lua_pushinteger(L, 3);
        lua_pushstring(L, "You can create complex machines, guns, bombs, and more.");
        lua_settable(L, -3);
    }
    catch (std::exception &e)
    {
        lua_pop(L, 1); // Remove the table
        lua_pushnil(L);
        lua_pushstring(L, e.what());
        return 2;
    }
    
    return 1;
}

/**
 * @brief Generate Powder Toy code from a description
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int generateCode(lua_State *L)
{
    auto *lsi = GetLSI();
    String description = tpt_lua_checkString(L, 1);
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lsi->gameController->OpenChatGPT();
        chatGPT = lsi->gameController->GetChatGPTController();
    }
    
    if (chatGPT)
    {
        // Prepare a prompt for code generation
        String prompt = "Generate Powder Toy code for: " + description + "\nPlease provide only the code without explanations.";
        
        // Send the message to ChatGPT
        chatGPT->SendMessage(prompt);
        
        // Wait for the response (this is a simplified approach)
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Get the response
        auto *model = chatGPT->GetModel();
        if (model)
        {
            auto messages = model->GetMessages();
            if (!messages.empty())
            {
                // Find the last assistant message
                for (auto it = messages.rbegin(); it != messages.rend(); ++it)
                {
                    if (!it->isUser)
                    {
                        tpt_lua_pushString(L, it->content);
                        return 1;
                    }
                }
            }
        }
    }
    
    lua_pushnil(L);
    return 1;
}

/**
 * @brief Learn from a conversation topic
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int learnTopic(lua_State *L)
{
    auto *lsi = GetLSI();
    String topic = tpt_lua_checkString(L, 1);
    
    // This is a placeholder for actual learning implementation
    // In a real implementation, you would store the topic and use it to improve responses
    
    lua_pushboolean(L, true);
    return 1;
}

void LuaChatGPT::Open(lua_State *L)
{
    static const luaL_Reg reg[] = {
        {"open", open},
        {"sendMessage", sendMessage},
        {"getLastResponse", getLastResponse},
        {"searchWeb", searchWeb},
        {"generateCode", generateCode},
        {"learnTopic", learnTopic},
        {nullptr, nullptr}
    };
    
    lua_newtable(L);
    luaL_register(L, nullptr, reg);
    lua_setglobal(L, "chatgpt");
}#include "LuaChatGPT.h"
#include "gui/game/GameController.h"
#include "gui/chatgpt/ChatGPTController.h"
#include "gui/chatgpt/ChatGPTModel.h"
#include "gui/chatgpt/ChatGPTView.h"
#include "client/http/Request.h"
#include "client/http/RequestManager.h"
#include "common/platform/Platform.h"
#include <thread>
#include <chrono>
#include "web_search.h"

/**
 * @brief Open the ChatGPT interface from Lua
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int open(lua_State *L)
{
    auto *lsi = GetLSI();
    lsi->gameController->OpenChatGPT();
    return 0;
}

/**
 * @brief Send a message to ChatGPT from Lua
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int sendMessage(lua_State *L)
{
    auto *lsi = GetLSI();
    String message = tpt_lua_checkString(L, 1);
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lsi->gameController->OpenChatGPT();
        chatGPT = lsi->gameController->GetChatGPTController();
    }
    
    if (chatGPT)
    {
        chatGPT->SendMessage(message);
        lua_pushboolean(L, true);
    }
    else
    {
        lua_pushboolean(L, false);
    }
    
    return 1;
}

/**
 * @brief Get the last response from ChatGPT
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int getLastResponse(lua_State *L)
{
    auto *lsi = GetLSI();
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lua_pushnil(L);
        return 1;
    }
    
    auto *model = chatGPT->GetModel();
    if (!model)
    {
        lua_pushnil(L);
        return 1;
    }
    
    auto messages = model->GetMessages();
    if (messages.empty())
    {
        lua_pushnil(L);
        return 1;
    }
    
    // Find the last assistant message
    for (auto it = messages.rbegin(); it != messages.rend(); ++it)
    {
        if (!it->isUser)
        {
            tpt_lua_pushString(L, it->content);
            return 1;
        }
    }
    
    lua_pushnil(L);
    return 1;
}

/**
 * @brief Search the web for information related to a query
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int searchWeb(lua_State *L)
{
    auto *lsi = GetLSI();
    String query = tpt_lua_checkString(L, 1);
    
    // Create a new table to store the search results
    lua_newtable(L);
    
    // Perform the web search
    try
    {
        // This is a placeholder for actual web search implementation
        // In a real implementation, you would call an external API or service
        
        // Simulate search results
        lua_pushinteger(L, 1);
        lua_pushstring(L, "The Powder Toy is a free physics sandbox game.");
        lua_settable(L, -3);
        
        lua_pushinteger(L, 2);
        lua_pushstring(L, "It simulates air pressure, velocity, heat, gravity and many interactions.");
        lua_settable(L, -3);
        
        lua_pushinteger(L, 3);
        lua_pushstring(L, "You can create complex machines, guns, bombs, and more.");
        lua_settable(L, -3);
    }
    catch (std::exception &e)
    {
        lua_pop(L, 1); // Remove the table
        lua_pushnil(L);
        lua_pushstring(L, e.what());
        return 2;
    }
    
    return 1;
}

/**
 * @brief Generate Powder Toy code from a description
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int generateCode(lua_State *L)
{
    auto *lsi = GetLSI();
    String description = tpt_lua_checkString(L, 1);
    
    // Get the ChatGPT controller
    auto *chatGPT = lsi->gameController->GetChatGPTController();
    if (!chatGPT)
    {
        lsi->gameController->OpenChatGPT();
        chatGPT = lsi->gameController->GetChatGPTController();
    }
    
    if (chatGPT)
    {
        // Prepare a prompt for code generation
        String prompt = "Generate Powder Toy code for: " + description + "\nPlease provide only the code without explanations.";
        
        // Send the message to ChatGPT
        chatGPT->SendMessage(prompt);
        
        // Wait for the response (this is a simplified approach)
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Get the response
        auto *model = chatGPT->GetModel();
        if (model)
        {
            auto messages = model->GetMessages();
            if (!messages.empty())
            {
                // Find the last assistant message
                for (auto it = messages.rbegin(); it != messages.rend(); ++it)
                {
                    if (!it->isUser)
                    {
                        tpt_lua_pushString(L, it->content);
                        return 1;
                    }
                }
            }
        }
    }
    
    lua_pushnil(L);
    return 1;
}

/**
 * @brief Learn from a conversation topic
 * 
 * @param L Lua state
 * @return Number of return values
 */
static int learnTopic(lua_State *L)
{
    auto *lsi = GetLSI();
    String topic = tpt_lua_checkString(L, 1);
    
    // This is a placeholder for actual learning implementation
    // In a real implementation, you would store the topic and use it to improve responses
    
    lua_pushboolean(L, true);
    return 1;
}

void LuaChatGPT::Open(lua_State *L)
{
    static const luaL_Reg reg[] = {
        {"open", open},
        {"sendMessage", sendMessage},
        {"getLastResponse", getLastResponse},
        {"searchWeb", searchWeb},
        {"generateCode", generateCode},
        {"learnTopic", learnTopic},
        {nullptr, nullptr}
    };
    
    lua_newtable(L);
    luaL_register(L, nullptr, reg);
    lua_setglobal(L, "chatgpt");
}