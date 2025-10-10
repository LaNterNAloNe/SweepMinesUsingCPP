#pragma once

#include "../include/visualize.hpp"

/* Draw begining of the game */
void drawBeginning(RenderWindow &window)
{
    // Draw a green rectangle as the "Start Game" button.
    drawRectangle(window, 100, 100, 300, 300, sf::Color::Green);
    // Draw the text "Start Game" on the rectangle.
    // drawText(window, 100, 100, 200, 50, "Start Game", sf::Color::White);
}

/* Draw the beginning page */
void pageBeginning(RenderWindow &window, Event &event, int &page) {
    drawBeginning(window);
}

