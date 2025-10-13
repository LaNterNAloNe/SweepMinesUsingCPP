#include "../include/visualize.hpp"

void initVisualize(RenderWindow &window, const std::string &title) {
    /* OUTPUT */
    cout << "\33[34m[INFO]\33[0m Initializing visualization window..." << endl;

    /* EXCUTION */
    // Initialize the visualization window.
    VideoMode desktopMode = VideoMode::getDesktopMode();
    // Set the window size to 50% of the desktop resolution and set the window unresizable.
    window.create(VideoMode(desktopMode.width / 2, desktopMode.width / 32 * 9), title, sf::Style::Titlebar | sf::Style::Close);

    // Set virtual coordinate system to 1920x1080 for consistency across different screen resolutions.
    sf::View view(sf::FloatRect(0.f, 0.f, VIRTUAL_WINDOW_SIZE_X, VIRTUAL_WINDOW_SIZE_Y));
    // Set graphic center
    view.setCenter(VIRTUAL_WINDOW_SIZE_X / 2, VIRTUAL_WINDOW_SIZE_Y / 2);
    window.setView(view);

    /* OUTPUT */
    cout << "\33[34m[INFO]\33[0m Visualization window initialized." << endl;
}

/* Mouse move event handler */
bool isMouseInsideWindow(const sf::RenderWindow &window, const sf::Event &event)
{
    return event.mouseMove.x >= 0 && event.mouseMove.x < window.getSize().x &&
           event.mouseMove.y >= 0 && event.mouseMove.y < window.getSize().y;
}

void mouseMoveTrail(sf::Event &event, sf::RenderWindow &window, std::vector<TrailPoint> &trail)
{
    // Get mouse position in world coordinates.
    sf::Vector2i pixelPos(event.mouseMove.x, event.mouseMove.y);
    // Check if the mouse is inside the window.
    if (!isMouseInsideWindow(window, event))
    {
        return;
    }

    // Ignore mouse button or key events, or code would try to read undefined member mouseMove.
    if (event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased 
        || event.type == Event::KeyPressed || event.type == Event::KeyReleased)
    {
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
            trail.end(),   // End of the vector.
            [](const TrailPoint &p)
            {
                return p.lifetime.getElapsedTime().asSeconds() > 0.5f;
            }),     // Define the condition to remove old points (here it need to check if the point's lifetime is greater than 0.5 seconds. if true, the point should be moved to the end["the end" is declared below as "trail.end()", means points that meet the condition would be moved to the end of the queue]).
        trail.end() // The new logical end of the vector after rearrangement. It tells the function where to stop erasing (from the new logical end to the actual end).
    );              // Finally, erase the old points from the new logical end to the actual end.
}

/* Mouse position judgement */
bool isMouseStayInArea(sf::RenderWindow &window, const sf::Event &event, sf::FloatRect area)
{
    // Get mouse position in real coordinates.
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    // Transform pixel position to virtual coordinates.
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    // Check if the mouse is inside the area.
    return area.contains(worldPos);
}

int isMouseClickInArea(sf::RenderWindow &window, const sf::Event &event, sf::FloatRect area)
{
    // Get mouse position in real coordinates.
    sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    // Check if the mouse click is inside the area.
    if (area.contains(worldPos))
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            return LEFTCLICK;
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            return RIGHTCLICK;
        }
        else 
        {
            return false;
        }
    }
    return false;
}



/* Drawing function */
// #Square
sf::FloatRect makeSquareArea(float x, float y, float size)
{
    return sf::FloatRect(x - size / 2.f, y - size / 2.f, size, size);
}

// #Rectangle
sf::FloatRect makeRectangleArea(float x, float y, float width, float height)
{
    return sf::FloatRect(x - width / 2.f, y - height / 2.f, width, height);
}
// Draw Rectangle, include square.
void drawRectangle(RenderWindow &window, float x1, float y1, float x2, float y2, sf::Color color)
{
    // Draw a rectangle with the given coordinates and color.
    sf::RectangleShape rectangle(sf::Vector2f(x2 - x1, y2 - y1));
    rectangle.setPosition(x1, y1);
    rectangle.setFillColor(color);

    // Draw the rectangle.
    window.draw(rectangle);
}

// #Text
sf::FloatRect makeTextArea(const sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    float width = bounds.width;
    float height = bounds.height;
    sf::Vector2f position = text.getPosition();

    return sf::FloatRect(position.x - width / 2.f, position.y - height / 2.f, width, height);
}

sf::Text createTextObject(
    const std::string &content, // Text content to display.
    unsigned int fontSize, // Font size for the text.
    sf::Color color, // Color of the text.
    int align, // 0=CENTER, 1=LEFT, 2=RIGHT
    sf::Vector2f position,
    const char *fontpath // Path to the font file.
)
{
    // Load font if not loaded yet.
    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded)
    {
        if (!font.loadFromFile("../font/" + std::string(fontpath)))
        {
            std::cout << "\33[31m[ERROR]\33[0m Failed to load font '" << fontpath << "'." << std::endl;
            return sf::Text(); // return empty text object if failed to load font.
        }
        fontLoaded = true;
    }

    // Create a text object with the given parameters.
    sf::Text text;
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(fontSize);
    text.setFillColor(color);

    // Set the origin of the text to its center.
    sf::FloatRect bounds = text.getLocalBounds();
    switch (align)
    {
    case LEFT: // align left
        text.setOrigin(bounds.left, bounds.top + bounds.height / 2.f);
        break;
    case RIGHT: // align right
        text.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2.f);
        break;
    default: // align center
        text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        break;
    }

    // finally, set the position of the text.
    text.setPosition(position);
    return text;
}

void drawText(sf::RenderWindow &window, const sf::Text &text)
{
    // Draw the text.
    window.draw(text);
}

// #Texture

// define texture cache as global variable
;

// Draw texture using path directly. (Not recommended unless necessary)
// It will directly load texture from file and draw it, which causes low performance.
bool drawTextureWithPath(sf::RenderWindow &window, float x, float y, float size, const std::string &path)
{
    // Create a texture object.
    sf::Texture texture;
    
    // Judge if size is valid.
    if (size <= 0)
    {
        std::cout << "\33[31m[ERROR]\33[0m Invalid size." << std::endl;
        return false;
    }

    // Load texture from file
    if (!texture.loadFromFile("../material/" + path))
    {
        std::cout << "\33[31m[ERROR]\33[0m Failed to load texture '" << path << "'." << std::endl;
        return false;
    }

    // Get original texture size
    sf::Vector2u originalSize = texture.getSize();
    if (originalSize.x == 0 || originalSize.y == 0)
    {
        std::cout << "\33[31m[ERROR]\33[0m Invalid texture size." << std::endl;
        return false;
    }

    // Calculate scale factor to make texture width = scale px
    float scaleFactor = size / static_cast<float>(originalSize.x);

    // Create sprite and apply scaling
    sf::Sprite sprite(texture);
    sprite.setScale(scaleFactor, scaleFactor);

    // Set origin to center for proper positioning
    sprite.setOrigin(originalSize.x / 2.f, originalSize.y / 2.f);
    sprite.setPosition(x, y);

    // Draw sprite
    window.draw(sprite);
    return true;
}

// Preload texture into cache.
// It will load texture from file and store it in cache, which can be used later.
// it is worth noting that when cached textures won't be used anymore,
// it is recommended to remove them from cache to free up memory.
void preloadTexture(const std::string &path, TextureCache &textureCache)
{
    sf::Texture texture;
    if (!texture.loadFromFile("../material/" + path))
    {
        std::cout << "\33[31m[ERROR]\33[0m Failed to load texture: " << path << std::endl;
        return;
    }
    textureCache[path] = std::move(texture);
    cout << "Loaded texture: " << path << endl;
}

// Draw texture from cache.
// It will draw texture from cache if it exists, otherwise it will return false.
bool drawCachedTexture(sf::RenderWindow &window, float x, float y, float size, const std::string &path, 
    TextureCache &textureCache)
{
    // find texture in cache
    auto it = textureCache.find(path);
    if (it == textureCache.end())
    {
        std::cout << "\33[31m[ERROR]\33[0m Texture not preloaded: " << path << std::endl;
        return false;
    }

    // get texture from cache
    const sf::Texture &texture = it->second;
    sf::Vector2u originalSize = texture.getSize();
    float scaleFactor = size / static_cast<float>(originalSize.x);

    // create sprite and apply scaling
    sf::Sprite sprite(texture);
    sprite.setScale(scaleFactor, scaleFactor);
    sprite.setOrigin(originalSize.x / 2.f, originalSize.y / 2.f);
    sprite.setPosition(x, y);

    // draw sprite
    window.draw(sprite);

    return true;
}

// Free preload texture cache.
void freePreloadTextureCache(TextureCache &textureCache)
{
    // Clear texture cache
    textureCache.clear();

    // output
    std::cout << "\033[32m[INFO]\033[0m Texture cache cleared." << std::endl;
}
