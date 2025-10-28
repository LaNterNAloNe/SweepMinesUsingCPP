// This file is for visualization-related declarations and includes. Using SFML for graphics. Handling IO operations.
#pragma once

#include "SFML/Graphics.hpp"
// #include "PageSetting.hpp" // Avoid circular include dependency. You know I crashed the code because of this.
#include <iostream>
#include <cmath>
#include <map> // include map header for cross-platform compatibility
#include <regex>
using sf::Event;
using sf::RenderWindow;
using sf::Sprite;
using sf::Texture;
using sf::VideoMode;
using std::cout;
using std::endl;

// Visual size of game window. Keep updating (When window resize).
// Define these as extern to allow access in other files.
extern unsigned int WindowSizeX;
extern unsigned int WindowSizeY;

// Define the valid input regex.
extern std::regex validInputRegex;

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
void checkWindowResize(sf::RenderWindow &window, sf::Event &event, bool isForceUpdate = false);
// Force window resize. (Set to specific size)
void forceWindowResize(sf::RenderWindow &window, int width, int height);

// Set window to fullscreen.
void setWindowToFullscreen(RenderWindow &window, const std::string &title);
// Set window to windowed mode.
void setWindowToWindowed(RenderWindow &window, const std::string &title);


/* Grocery */
// Display the current FPS on the window.
void displayFPS(RenderWindow &window);


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
sf::Text createTextObject(const std::string &content, unsigned int fontSize, sf::Color color = sf::Color::Black, int align = CENTER, sf::Vector2f position = sf::Vector2f(0.f, 0.f), const char *fontpath = "font.ttf");
/*****************************************
** Define a class for visual text.
** \attention: 
        This class DO NOT manage the parameter of the instance. But boast its text object.
        You can change parameters in text object and draw it to get ideal result.
        Please manage them in the specific class. Like defining functions that return relative value.
** \example: 
        CVisualText startGameButtonText;
        int updateStartGameButtonTextSize() const { return WindowSizeX / 1920 * 40; }
        sf::Vector2f updateStartGameButtonPosition() const { return sf::Vector2f(WindowSizeX * 0.5, WindowSizeY * 0.6); }
*****************************************/
class CVisualText
{
public:
    // Normal constructor.
    CVisualText(const std::string &content, unsigned int fontSize, sf::Color color, Align align, sf::Vector2f position) : 
        content(content), fontSize(fontSize), color(color), align(align) { updateWhenWindowResize(position); }
    // Copy constructor.
    CVisualText(const CVisualText &other) : 
        content(other.content), fontSize(other.fontSize), color(other.color), align(other.align) { updateWhenWindowResize(other.textObject.getPosition()); }
    // Default constructor.
    CVisualText() { /* Please attention that this constructor is not recommended to use, unless you just create a object first and check if you initialize the object's parameter. If not, critical errors could happen. */ }

    std::string content; // Content of the text.
    unsigned int fontSize; // Font size of the text, commonly decide its height.
    sf::Color color; // Color of the text.
    Align align; // LEFT, CENTER, RIGHT
    sf::Text textObject; // Text object. Change scale or other parameters directly and draw the text.

    // Update the area of the text. Using new position passed by specific page class.
    void updateWhenWindowResize(sf::Vector2f newPosition) 
    {
        textObject = createTextObject(content, fontSize, color, align, newPosition);
    }
};

sf::FloatRect makeTextArea(const sf::Text &text);
void drawText(sf::RenderWindow &window, const CVisualText &text);


// #Texture
/*****************************************
** Define a class for visual texture.
** \attention: 
        This class DO NOT manage the parameter of the instance, and DO NOT store the texture file.
        So change parameter of the texture directly to get ideal result.
        Please manage them in the specific class. Like defining functions that return relative value.
** \example: 
        CVisualTexture exitButtonTexture("texture/exit.png", updateExitTexturePosition(), updateExitTextureSize());
        sf::Vector2f updateExitTexturePosition() const { return sf::Vector2f(WindowSizeX * 0.05f, WindowSizeX * 0.05f); }
        sf::Vector2f updateExitTextureSize() const { return sf::Vector2f(WindowSizeX / 1920 * 50, WindowSizeX / 1920 * 50); }
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
    CVisualTexture() { /* Please attention that this constructor is not recommended to use, unless you just create a object first and check if you initialize the object's parameter. If not, critical errors could happen. */ }

    std::string path; // Path to the texture file.
    sf::Vector2f position; // Position of the texture.
    sf::Vector2f size; // Size of the texture.
    float scale = 1.f; // Scale of the texture, which is outside setting that is convinient for scaling.
    sf::FloatRect area; // Area of the texture.

    // Update the area of the texture. Using new position and size passed by specific page class.
    void updateWhenWindowResize(sf::Vector2f newPosition, sf::Vector2f newSize) 
    { 
        position = newPosition;
        size = newSize;
        area = makeRectangleArea(position.x, position.y, size.x, size.y);
    }
};

// Texture cache.
typedef std::map<std::string, sf::Texture> TextureCache;

bool drawTextureWithPath(RenderWindow &window, CVisualTexture &tex);
void preloadTexture(const std::string &path, TextureCache &textureCache);
bool drawCachedTexture(RenderWindow &window, CVisualTexture &tex, TextureCache &textureCache);
void freePreloadTextureCache(TextureCache &textureCache);


// #Input bar
/*****************************************
** Define a class for input bar.
** \attention: 
        This class DO NOT manage the parameter of the instance, and DO NOT store the texture file.
        So change parameter of the texture directly to get ideal result.
        Please manage them in the specific class. Like defining functions that return relative value.
** \example: 
        customMapInputBox_X(updateCustomMapInputBox_XPosition(), updateCustomMapInputBox_XSize(), "font.ttf", 40, "X", 2),
        sf::Vector2f updateCustomMapInputBox_XPosition() { return sf::Vector2f(WindowSizeX * 0.4f, WindowSizeY * 0.5f); }
        sf::Vector2f updateCustomMapInputBox_XSize() { return sf::Vector2f(WindowSizeX / 1920.f * 200.f, WindowSizeX / 1920.f * 100.f); }
        sf::Vector2f updateCustomMapInputBox_XFontSize() { return sf::Vector2f(WindowSizeX / 1920.f * 40.f, WindowSizeX / 1920.f * 40.f); }
*****************************************/
class CInputBox
{
public:
    // Normal constructor.
    CInputBox(const sf::Vector2f &position,
              const sf::Vector2f &size,
              const std::string &fontPath,
              unsigned int characterSize,
              const std::string &placeholderText = "",
              std::size_t maxLength = 100);

    // Set the input box active state (controlled by external).
    void setActive(bool active) { this->active = active; }

    // Get current active state.
    bool isActive() const { return active; }

    // Handle input events (only called when active).
    void handleEvent(const sf::Event &event);

    // Render the input box.
    void draw(sf::RenderWindow &window) const
    {
        window.draw(box);
        window.draw(text);
        if (inputString.empty())
            window.draw(placeholder);
    }

    // Set the input box content.
    void setText(const std::string &text) {this->inputString = text;}

    // Get the current input content.
    std::string getText() const {return inputString;}

    // Get global bounds.
    sf::FloatRect getGlobalBounds() const {return box.getGlobalBounds();}

    // Set the placeholder text.
    void setPlaceholder(const std::string &text) {this->placeholder.setString(text);}

    // Set the maximum length of the input string.
    void setMaxLength(std::size_t length) {this->maxLength = length;}

    // Check if the mouse click is in the box area.
    bool contains(const sf::Vector2f &point) const {return box.getGlobalBounds().contains(point);}

    // Update visualization when window resized.
    void updateWhenWindowResize(sf::Vector2f newPosition, sf::Vector2f newSize, sf::Vector2f newFontSize);

    // Get the position of the input box.
    sf::Vector2f getPosition() const {return box.getPosition();}

private:
    // Graphic elements.
    sf::RectangleShape box;
    sf::Font font; // The class must behold a font object or text object and placeholder object will not find font and crash the game.
    sf::Text text;
    sf::Text placeholder;

    // State management.
    bool active = false;
    std::string inputString;
    std::size_t maxLength;

    // Style.
    sf::Color textColor = sf::Color::Black; // Defalt black.
    sf::Color placeholderColor = sf::Color(128, 128, 128, 128); // Defalt semi-transparent grey.
};


/* Check function */
bool isStringAllNum(const std::string &str); // Check if the string is all numbers.




/* Here are some notes that can remember you when create visual window */
/* Console text color ANSI escape sequence
// "\033[01;31m" // Red
// "\033[01;32m" // Green
// "\033[01;33m" // Yellow
// "\033[01;34m" // Blue
// "\033[01;35m" // Purple
// "\033[01;36m" // Cyan
// "\033[01;37m" // White
// "\033[00m"    // Reset color
*/
