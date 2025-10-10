// This file is for visualization-related declarations and includes. Using SFML for graphics.

#include "SFML/Graphics.hpp"
using sf::RenderWindow;
using sf::Event;
using sf::Sprite;
using sf::Texture;
using sf::Vector2f;


/* Visualize initialization */
void initVisualize(unsigned int width, unsigned int height, RenderWindow &window, const std::string &title) {
    // Initialize the visualization window.
    window.create(sf::VideoMode({width, height}), title);
}
