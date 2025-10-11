// Page.hpp
/*
 * Bass file for page management in the application.
*/

#pragma once

#include "SFML/Graphics.hpp"

enum PageType
{
    BEGINNING_PAGE,
    GAME_PAGE,
    ENDING_PAGE
};

class CPage
{
public:
    // Define virtual functions for page management. 
    // These functions should be implemented in derived classes.
    // Functions functioning as follows:
    // handleEvent: Handle user input events for the page.
    // update: Update the state of the page.
    // render: Draw the page on the window.
    virtual void handleEvent(sf::RenderWindow &window, sf::Event &event) = 0;
    virtual void update(sf::RenderWindow &window) = 0;
    virtual void render(sf::RenderWindow &window) = 0;
    virtual ~CPage() {}
};

// Get the name of the page, coloring the name string.
const char* getPageName (const int page) {
    switch (page)
    {
    case BEGINNING_PAGE:
        return "\033[36mBEGINNING_PAGE\033[0m";
    case GAME_PAGE:
        return "\033[36mGAME_PAGE\033[0m";
    case ENDING_PAGE:
        return "\033[36mENDING_PAGE\033[0m";
    default:
        return "\033[36m?UNKNOWN?\033[0m";
    }
}

// Check if the page exists in the map.
bool isPageExist(const int currentPage, const std::map<int, std::unique_ptr<CPage>> &pages) {
    return pages.find(currentPage) != pages.end();
}