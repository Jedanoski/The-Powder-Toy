#pragma once
#include "common/String.h"
#include <vector>

/**
 * @brief Result of a web search
 */
struct WebSearchResult
{
    String title;       ///< Title of the search result
    String description; ///< Description or snippet of the search result
    String url;         ///< URL of the search result
    
    /**
     * @brief Constructor for WebSearchResult
     * 
     * @param title_ Title of the search result
     * @param description_ Description or snippet of the search result
     * @param url_ URL of the search result
     */
    WebSearchResult(String title_, String description_, String url_) :
        title(title_), description(description_), url(url_) {}
};

/**
 * @brief Search the web for information
 * 
 * @param query The search query
 * @return Vector of search results
 */
std::vector<WebSearchResult> SearchWeb(String query);#pragma once
#include "common/String.h"
#include <vector>

/**
 * @brief Result of a web search
 */
struct WebSearchResult
{
    String title;       ///< Title of the search result
    String description; ///< Description or snippet of the search result
    String url;         ///< URL of the search result
    
    /**
     * @brief Constructor for WebSearchResult
     * 
     * @param title_ Title of the search result
     * @param description_ Description or snippet of the search result
     * @param url_ URL of the search result
     */
    WebSearchResult(String title_, String description_, String url_) :
        title(title_), description(description_), url(url_) {}
};

/**
 * @brief Search the web for information
 * 
 * @param query The search query
 * @return Vector of search results
 */
std::vector<WebSearchResult> SearchWeb(String query);#pragma once
#include "common/String.h"
#include <vector>

/**
 * @brief Result of a web search
 */
struct WebSearchResult
{
    String title;       ///< Title of the search result
    String description; ///< Description or snippet of the search result
    String url;         ///< URL of the search result
    
    /**
     * @brief Constructor for WebSearchResult
     * 
     * @param title_ Title of the search result
     * @param description_ Description or snippet of the search result
     * @param url_ URL of the search result
     */
    WebSearchResult(String title_, String description_, String url_) :
        title(title_), description(description_), url(url_) {}
};

/**
 * @brief Search the web for information
 * 
 * @param query The search query
 * @return Vector of search results
 */
std::vector<WebSearchResult> SearchWeb(String query);