// This file is for visualization-related declarations and includes. Using SFML for graphics. Handling IO operations.
#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>
#include <map>
using sf::Event;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::VideoMode;
using std::cout;
using std::endl;

// Set virtual window size to 1920x1080 for consistency across different screen resolutions.
#define VIRTUAL_WINDOW_SIZE_X 1920
#define VIRTUAL_WINDOW_SIZE_Y 1080

// Get the area of a button using Marco Function
// ##Square
#define MAKE_AREA_SQUARE(x, y, size) sf::FloatRect( \
    (x) - (size) / 2.f,                      \
    (y) - (size) / 2.f,                      \
    (size),                                  \
    (size))
// ##Rectangle
#define MAKE_AREA_RECT(x, y, width, height) sf::FloatRect( \
    (x) - (width) / 2.f,                     \
    (y) - (height) / 2.f,                    \
    (width),                                 \
    (height))


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
enum MouseClickResult {
    LEFTCLICK = 1,
    RIGHTCLICK = 2,
};

bool isMouseStayInArea(sf::RenderWindow &window, const sf::Event &event, sf::FloatRect area);
int isMouseClickInArea(sf::RenderWindow &window, const sf::Event &event, sf::FloatRect area);

/* Drawing function */
enum Align {
    LEFT = 0,
    RIGHT = 1,
    CENTER = 2,
};

// #Rectangle
void drawRectangle(RenderWindow &window, float x1, float y1, float x2, float y2, sf::Color color);

// #Text
sf::FloatRect makeTextArea(const sf::Text &text);
sf::Text createTextObject(const std::string &content, unsigned int fontSize, sf::Color color = sf::Color::Black, int align = CENTER, 
    sf::Vector2f position = sf::Vector2f(0.f, 0.f), const char *fontpath = "font.ttf");
void drawText(sf::RenderWindow &window, const sf::Text &text);

// #Texture
bool drawTextureWithPath(RenderWindow &window, float x, float y, float size, const std::string &path);
void preloadTexture(const std::string &path, std::map<std::string, sf::Texture> &textureCache);
bool drawCachedTexture(RenderWindow &window, float x, float y, float size, const std::string &pat,
                       std::map<std::string, sf::Texture> &textureCache);
void freePreloadTextureCache(std::map<std::string, sf::Texture> &TextureCache);