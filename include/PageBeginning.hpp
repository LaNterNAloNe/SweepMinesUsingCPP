// PageBeginning.hpp
/*
 * Beginning page of the game.
*/

#pragma once

#include "../include/Page.hpp"
#include "../include/visualize.hpp"

/* Unique pointer to the beginning page */
class CPageBeginning : public CPage {
public:
    // See the comments in Page.hpp for the function's functionality.
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void render(sf::RenderWindow &window) override;
    ~CPageBeginning() override {}
};

/* Draw begining of the game */
void CPageBeginning::render(sf::RenderWindow &window) {
    // Draw a green rectangle as the "Start Game" button.
    drawRectangle(window, 100, 100, 300, 300, sf::Color::Green);
    // Draw the text "Start Game" on top of the button.
}

/* Update beginning page */
void CPageBeginning::update(sf::RenderWindow &window) {
    // Currently, no dynamic content to update on the beginning page.
}

/* Handle events on the beginning page */
void CPageBeginning::handleEvent(sf::RenderWindow &window, sf::Event &event) {
    // Check if the "Start Game" button is clicked.
    if (isMouseInArea(window, event, 100, 100, 300, 300)) {
        cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Start Game' button clicked." << endl;
        // Transition to the game page (not implemented here).
    }
}

