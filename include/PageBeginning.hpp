// PageBeginning.hpp
/*
 * Beginning page of the game.
*/

#pragma once

#include "Page.hpp"
#include "visualize.hpp"

// Exit button parameter
#define exitButtonX 50
#define exitButtonY 50
#define exitButtonSize 50
#define exitButtonArea MAKE_AREA_SQUARE(exitButtonX, exitButtonY, exitButtonSize)



/* Unique pointer to the beginning page */
class CPageBeginning : public CPage 
{
public:
    // See the comments in Page.hpp for the function's functionality.
    void handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages) override;
    void update(sf::RenderWindow &window, sf::Event event) override;
    void render(sf::RenderWindow &window, sf::Event event) override;
    ~CPageBeginning() override {}
private:
    // Hover state of the beginning page. (To decide which button's apperance changes)
    enum hoverState
    {
        NONE = 0,
        EXIT = 1,
        START_GAME = 2,
    };
    hoverState currentHoverState = NONE;

    // Text object of the beginning page.
    sf::Text startGameButtonText = createTextObject("Start Game", 40, sf::Color::Black, CENTER,
                                                    sf::Vector2f(VIRTUAL_WINDOW_SIZE_X / 2, VIRTUAL_WINDOW_SIZE_Y / 2 + 50));
    sf::Text exitButtonText = createTextObject("Exit", 40, sf::Color::Transparent, LEFT,
                                                sf::Vector2f(exitButtonX + exitButtonSize, exitButtonY));
};

