#pragma once

#include "visualize.hpp"

// Output debug information about mouse button press events.
void debugOutput(sf::RenderWindow &window, sf::Event event);

// Show a rectangle on the window.
void showRect(sf::RenderWindow &window, sf::FloatRect rect);

// Show a line on the window.
void showLine(sf::RenderWindow &window, sf::Vector2f start, sf::Vector2f end);