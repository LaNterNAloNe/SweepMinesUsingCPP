#pragma once

#include "visualize.hpp"

// Output debug information about mouse button press events.
void debugOutput(RenderWindow &window, Event event);

// Show a rectangle on the window.
void showRect(RenderWindow &window, sf::FloatRect rect);

// Show a line on the window.
void showLine(RenderWindow &window, sf::Vector2f start, sf::Vector2f end);