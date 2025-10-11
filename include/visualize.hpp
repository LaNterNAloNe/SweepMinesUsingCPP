// This file is for visualization-related declarations and includes. Using SFML for graphics. Handling IO operations.
#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>
using sf::Event;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::VideoMode;
using std::cout;
using std::endl;


/* Visualize initialization */
void initVisualize(RenderWindow &window, const std::string &title);

/* Mouse move event handler */
struct TrailPoint {
    sf::Vector2f position;
    sf::Color color;
    sf::Clock lifetime;
};

bool isMouseInsideWindow(const sf::RenderWindow &window, const sf::Event &event);
void mouseMoveTrail(sf::Event &event, sf::RenderWindow &window, std::vector<TrailPoint> &trail);
void updateTrail(std::vector<TrailPoint> &trailPoints, RenderWindow &window);

/* Mouse position judgement */
bool isMouseInArea(sf::RenderWindow &window, const sf::Event &event, float x1, float y1, float x2, float y2);

/* Drawing function */
void drawRectangle(RenderWindow &window, float x1, float y1, float x2, float y2, sf::Color color);
void drawText(RenderWindow &window, float x1, float y1, float x2, float y2, const std::string &textString, sf::Color color);




