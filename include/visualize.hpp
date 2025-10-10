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
void initVisualize(RenderWindow &window, const std::string &title) {
    /* OUTPUT */
    cout << "\33[36m[INFO]\33[0m Initializing visualization window..." << endl;

    /* EXCUTION */
    // Initialize the visualization window.
    VideoMode desktopMode = VideoMode::getDesktopMode();
    // Set the window size to 50% of the desktop resolution and set the window unresizable.
    window.create(VideoMode(desktopMode.width / 2, desktopMode.width / 32 * 9), title, sf::Style::Titlebar | sf::Style::Close);

    // Set virtual coordinate system to 1920x1080 for consistency across different screen resolutions.
    sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
    // Set graphic center
    view.setCenter(1920.f / 2, 1080.f / 2);
    window.setView(view);

    /* OUTPUT */
    cout << "\33[36m[INFO]\33[0m Visualization window initialized." << endl;
}

/* Mouse move event handler */
struct TrailPoint {
    sf::Vector2f position;
    sf::Color color;
    sf::Clock lifetime;
};

bool isMouseInsideWindow(const sf::RenderWindow &window, const sf::Event &event) {
    return event.mouseMove.x >= 0 && event.mouseMove.x < window.getSize().x &&
           event.mouseMove.y >= 0 && event.mouseMove.y < window.getSize().y;
}


void mouseMoveTrail(sf::Event &event, sf::RenderWindow &window, std::vector<TrailPoint> &trail) {
    // Get mouse position in world coordinates.
    sf::Vector2i pixelPos(event.mouseMove.x, event.mouseMove.y);
    // Check if the mouse is inside the window.
    if (!isMouseInsideWindow(window, event)) {
        return;
    }

    // Ignore mouse button events, or code would try to read undefined member mouseMove.
    if (event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased) {
        return;
    }
    // And convert it to world coordinates.
    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

    // Add a new trail point.
    TrailPoint point;
    point.position = worldPos;
    point.color = sf::Color::Red;
    point.lifetime.restart();

    trail.push_back(point);
}


void updateTrail(std::vector<TrailPoint> &trail, sf::RenderWindow &window)
{
    // Create a triangle strip for the trail
    std::vector<sf::Vertex> strip;

    // Iterate through trail points to create segments between consecutive points.
    for (size_t i = 1; i < trail.size(); ++i)
    {

        const auto &p0 = trail[i - 1];
        const auto &p1 = trail[i];

        // Get the age of each point in seconds.
        float age0 = p0.lifetime.getElapsedTime().asSeconds();
        float age1 = p1.lifetime.getElapsedTime().asSeconds();

        // Skip points older than 0.5 seconds
        if (age0 > 0.5f || age1 > 0.5f)
            continue;

        // Calculate colors with fading alpha based on age.
        sf::Color c0 = p0.color;
        sf::Color c1 = p1.color;
        c0.a = static_cast<sf::Uint8>(255 * (1.0f - age0 / 0.5f));
        c1.a = static_cast<sf::Uint8>(255 * (1.0f - age1 / 0.5f));

        // Calculate width with fading effect based on age.
        // Now the width decreases from 8 to 0 over 0.5 seconds.
        // Easily, we can know that w0 > w1 if age0 < age1. So that we can create a tapering effect.
        float w0 = 8.f * (1.0f - age0 / 0.5f);
        float w1 = 8.f * (1.0f - age1 / 0.5f);

        // Calculate direction and normal vector for the segment.
        // Now getting the direction vector between two points.
        sf::Vector2f dir = p1.position - p0.position;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len == 0) // Avoid division by zero.
            continue;
        // Get normal vector for the segment.
        sf::Vector2f normal(-dir.y / len, dir.x / len);

        // Now constructing two triangle points (left and right offset) for the segment.
        strip.push_back(sf::Vertex(p0.position + normal * w0, c0));
        strip.push_back(sf::Vertex(p0.position - normal * w0, c0));
        strip.push_back(sf::Vertex(p1.position + normal * w1, c1));
        strip.push_back(sf::Vertex(p1.position - normal * w1, c1));
    }

    // After constructing the triangle strip, draw it if not empty.
    if (!strip.empty())
        window.draw(&strip[0], strip.size(), sf::TrianglesStrip);

    // Remove old points (older than 0.5 seconds).
    trail.erase(
        std::remove_if( // Rearrange the vector to move old points to the end and get new logical end. It can move elements to the end of the queue.
            // Then tell the function the area of it should check (from the beginning to the end ).
            trail.begin(), // Start of the vector.
            trail.end(), // End of the vector.
            [](const TrailPoint &p)
            {
                return p.lifetime.getElapsedTime().asSeconds() > 0.5f;
            }), // Define the condition to remove old points (here it need to check if the point's lifetime is greater than 0.5 seconds. if true, the point should be moved to the end["the end" is declared below as "trail.end()", means points that meet the condition would be moved to the end of the queue]).
        trail.end() // The new logical end of the vector after rearrangement. It tells the function where to stop erasing (from the new logical end to the actual end).
    ); // Finally, erase the old points from the new logical end to the actual end.
}


/* Drawing function */
void drawRectangle(RenderWindow &window, float x1, float y1, float x2, float y2, sf::Color color) {
    // 
    sf::RectangleShape rectangle(sf::Vector2f(x2 - x1, y2 - y1));
    rectangle.setPosition(x1, y1);
    rectangle.setFillColor(color);
    window.draw(rectangle);
}

void drawText(RenderWindow &window, float x1, float y1, float x2, float y2, const std::string &textString, sf::Color color) {
    float width = x2 - x1;
    float height = y2 - y1;
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.loadFromFile("../font/font.ttf")) {
            cout << "\33[31m[ERROR]\33[0m Failed to load font 'font.ttf'." << endl;
            return;
        } else {
            fontLoaded = true;
        }
    }

    sf::Text text;
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(static_cast<unsigned int>(height * 0.6f)); // Set character size relative to rectangle height.
    text.setFillColor(color);

    // Center the text within the rectangle.
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(x1 + width / 2.0f, y1 + height / 2.0f);

    window.draw(text);
}


/* Mouse click */
bool isMouseInArea(sf::RenderWindow &window, const sf::Event &event, float x1, float y1, float x2, float y2) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        return worldPos.x >= x1 && worldPos.x <= x2 &&
               worldPos.y >= y1 && worldPos.y <= y2;
    }
    return false;
}
