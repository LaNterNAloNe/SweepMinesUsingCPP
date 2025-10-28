// Page.hpp
/*
 * Bass file for page management in the application.
*/

#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <iostream>
#include <map> // include map header for cross-platform compatibility

using std::cout;
using std::endl;

enum PageType
{
    BEGINNING_PAGE,
    SETTING_PAGE,
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
    virtual void handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages) = 0;
    virtual void update(sf::RenderWindow &window, sf::Event event) = 0;
    virtual void render(sf::RenderWindow &window, sf::Event event) = 0;
    virtual ~CPage() {}

protected:
    // Store the last window size. Each derived class will inherit it and store in specific memory.
    sf::Vector2f lastWindowSize = {0, 0}; 
};


const std::string getPageName(const int page);
bool isPageExist(const int currentPage, const std::map<int, std::unique_ptr<CPage>> &pages);
void changePage(sf::RenderWindow &window, int &currentPage, int newPage, const std::map<int, std::unique_ptr<CPage>> &pages);
