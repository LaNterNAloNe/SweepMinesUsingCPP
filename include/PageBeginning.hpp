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
#define exitButtonArea MAKE_AREA(exitButtonX, exitButtonY, exitButtonSize)


/* Unique pointer to the beginning page */
class CPageBeginning : public CPage 
{
public:
    // See the comments in Page.hpp for the function's functionality.
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void render(sf::RenderWindow &window) override;
    ~CPageBeginning() override {}
};

struct SPageBeginningParameter {
    // Parameters for the beginning page.
};
