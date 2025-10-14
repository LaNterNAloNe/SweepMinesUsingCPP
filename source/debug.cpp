#include "../include/debug.hpp"

// Output debug information about mouse button press events.
void debugOutput(RenderWindow &window, Event event)
{
    if (event.type == Event::MouseButtonPressed)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f virtualPos = window.mapPixelToCoords(pixelPos);

        cout << "\33[32m[DEBUG]\33[0m Mouse button pressed at (" << virtualPos.x << ", " << virtualPos.y << "). (Virtual Coordinates)" << endl;
    }
}

void showRect(RenderWindow &window, sf::FloatRect rect)
{
    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setPosition(rect.left, rect.top);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);
    shape.setFillColor(sf::Color::Transparent);
    window.draw(shape);
}

void showLine(RenderWindow &window, sf::Vector2f start, sf::Vector2f end)
{
    sf::Vertex line[] =
    {
        sf::Vertex(start, sf::Color::Red),
        sf::Vertex(end, sf::Color::Red)
    };
    window.draw(line, 2, sf::Lines);
}