// This file is for visualization-related declarations and includes. Using SFML for graphics. Handling IO operations.
#pragma once

#include "SFML/Graphics.hpp"
#include "PageSetting.hpp"
#include <iostream>
#include <cmath>
#include <map> // include map header for cross-platform compatibility
using sf::Event;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::VideoMode;
using std::cout;
using std::endl;

extern unsigned int virtualWindowSizeX;
extern unsigned int virtualWindowSizeY;

// LEGACY, do not use unless neccessary
// Get the area of a button using Marco Function
// // ##Square
// #define MAKE_AREA_SQUARE(x, y, size) sf::FloatRect( \
//     (x) - (size) / 2.f,                      \
//     (y) - (size) / 2.f,                      \
//     (size) * 1.f,                                  \
//     (size) * 1.f)
// // ##Rectangle
// #define MAKE_AREA_RECT(x, y, width, height) sf::FloatRect( \
//     (x) - (width) / 2.f,                     \
//     (y) - (height) / 2.f,                    \
//     (width) * 1.f,                              \
//     (height) * 1.f)


/* Visualize initialization */
void initVisualize(RenderWindow &window, const std::string &title);
// Check if window size is resized by user and take actions.
void checkWindowResize(sf::RenderWindow &window, sf::Event &event);


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
sf::FloatRect makeSquareArea(float x, float y, float size);
sf::FloatRect makeRectangleArea(float x, float y, float width, float height);
void drawRectangle(RenderWindow &window, float x1, float y1, float x2, float y2, sf::Color color);


// #Text
sf::Text createTextObject(const std::string &content, unsigned int fontSize, sf::Color color = sf::Color::Black, int align = CENTER,
                          sf::Vector2f position = sf::Vector2f(0.f, 0.f), const char *fontpath = "font.ttf");
/*****************************************
** Define a class for visual text.
** \attention: This class DO NOT manage the parameter of the instance.
               Please manage them in the specific page class. Like defining functions that return relative value.
** \example: CVisualText startGameButtonText;
             int updateStartGameButtonTextSize() const { return virtualWindowSizeX / 1920 * 40; }
             sf::Vector2f updateStartGameButtonPosition() const { return sf::Vector2f(virtualWindowSizeX * 0.5, virtualWindowSizeY * 0.6); }
*****************************************/
class CVisualText
{
public:
    // Constructor.
    CVisualText(const std::string &content, unsigned int fontSize, sf::Color color, Align align, sf::Vector2f position) : 
        content(content), fontSize(fontSize), color(color), align(align), position(position) { updateWhenWindowResize(position); }

    std::string content; // Content of the text.
    unsigned int fontSize; // Font size of the text, commonly decide its height.
    sf::Color color; // Color of the text.
    Align align; // LEFT, CENTER, RIGHT
    sf::Vector2f position; // Position of the text.
    sf::Text textObject; // Text object.
    sf::FloatRect area; // Area of the text.

    // Update the area of the text. Using new position passed by specific page class.
    void updateWhenWindowResize(sf::Vector2f newPosition) 
    {
        textObject = createTextObject(content, fontSize, color, align, newPosition);
        area = textObject.getGlobalBounds();
    }
};

sf::FloatRect makeTextArea(const sf::Text &text);
void drawText(sf::RenderWindow &window, const sf::Text &text);


// #Texture
/*****************************************
** Define a class for visual texture.
** \attention: This class DO NOT manage the parameter of the instance.
               Please manage them in the specific page class. Like defining functions that return relative value.
** \example: CVisualTexture exitButtonTexture("texture/exit.png", updateExitTexturePosition(), updateExitTextureSize());
             sf::Vector2f updateExitTexturePosition() const { return sf::Vector2f(virtualWindowSizeX * 0.05f, virtualWindowSizeX * 0.05f); }
             sf::Vector2f updateExitTextureSize() const { return sf::Vector2f(virtualWindowSizeX / 1920 * 50, virtualWindowSizeX / 1920 * 50); }
*****************************************/
class CVisualTexture
{
public:
    // Parameter constructor.
    CVisualTexture(const std::string &path, sf::Vector2f position, sf::Vector2f size) : 
        path(path), position(position), size(size) { updateWhenWindowResize(position, size); }
    // Copy constructor.
    CVisualTexture(const CVisualTexture &other, const std::string &path) : 
        path(path), position(other.position), size(other.size) { updateWhenWindowResize(position, size); }
    // Default constructor.
    CVisualTexture() : path(""), position(sf::Vector2f(0.f, 0.f)), size(sf::Vector2f(0.f, 0.f)) {}

    std::string path; // Path to the texture file.
    sf::Vector2f position; // Position of the texture.
    sf::Vector2f size; // Size of the texture.
    sf::FloatRect area; // Area of the texture.

    // Update the area of the texture. Using new position and size passed by specific page class.
    void updateWhenWindowResize(sf::Vector2f newPosition, sf::Vector2f newSize) 
    { 
        position = newPosition;
        size = newSize;
        area = makeRectangleArea(position.x, position.y, size.x, size.y);
    }
};

typedef std::map<std::string, sf::Texture> TextureCache;
bool drawTextureWithPath(RenderWindow &window, CVisualTexture &tex);
void preloadTexture(const std::string &path, TextureCache &textureCache);
bool drawCachedTexture(RenderWindow &window, float x, float y, float size, const std::string &path, TextureCache &textureCache);
void freePreloadTextureCache(TextureCache &textureCache);
