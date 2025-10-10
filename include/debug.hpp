#pragma once

#include "../include/visualize.hpp"

void debugOutput(RenderWindow &window, Event event) {
    if (event.type == Event::MouseButtonPressed)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f virtualPos = window.mapPixelToCoords(pixelPos);

        cout << "\33[32m[DEBUG]\33[0m Mouse button pressed at (" << virtualPos.x << ", " << virtualPos.y << "). (Virtual Coordinates)" << endl;
    }
}