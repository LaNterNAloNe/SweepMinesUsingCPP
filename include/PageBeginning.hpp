// PageBeginning.hpp
/*
 * Beginning page of the game.
*/

#pragma once

#include "Page.hpp"
#include "visualize.hpp"
#include "debug.hpp"


/* Unique pointer to the beginning page */
class CPageBeginning : public CPage 
{
public:
    // Constructor.
    CPageBeginning() : 
        mineTexture("page_beginning/mine.png", updateMineTexturePosition(), updateMineTextureSize()),
        exitButtonTexture("page_beginning/exit.png", updateExitTexturePosition(), updateExitTextureSize()),
        startGameButtonText("Start Game", updateStartGameButtonTextSize(), sf::Color::Black, CENTER, updateStartGameButtonTextPosition()),
        exitButtonText("Exit", updateExitTextSize(), sf::Color::Transparent, LEFT, updateExitTextPosition()),
        exitButtonTextureHover(exitButtonTexture, "page_beginning/exit_hover.png") {}
    // See the comments in Page.hpp for the function's functionality.
    void handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages) override;
    void update(sf::RenderWindow &window, sf::Event event) override;
    void render(sf::RenderWindow &window, sf::Event event) override;
    ~CPageBeginning() override {}

    // Preload texture of the beginning page.
    void preloadBeginningPageTexture();
    void freeBeginningPageTexture();

private:
    // Hover state of the beginning page. (To decide which button's apperance changes)
    enum hoverState
    {
        NONE = 0,
        EXIT = 1,
        START_GAME = 2,
    };
    hoverState currentHoverState = NONE;

    // Texture of the beginning page.
    TextureCache beginningPageTexture;
    bool isTextureLoaded = false;

    // Mine texture.
    CVisualTexture mineTexture;
    sf::Vector2f updateMineTextureSize() const { return sf::Vector2f(
        std::min(virtualWindowSizeX / 1920.f * 200.f, virtualWindowSizeY / 1080.f * 200.f), 
        std::min(virtualWindowSizeX / 1920.f * 200.f, virtualWindowSizeY / 1080.f * 200.f)); }
    sf::Vector2f updateMineTexturePosition() const { return sf::Vector2f(virtualWindowSizeX * 0.5f, virtualWindowSizeY * 0.4f); }

    // Text object of the beginning page.
    CVisualText startGameButtonText;
    int updateStartGameButtonTextSize() const { return std::min(virtualWindowSizeX / 1920.f * 40.f, virtualWindowSizeY / 1080.f * 40.f); }
    sf::Vector2f updateStartGameButtonTextPosition() const { return sf::Vector2f(virtualWindowSizeX * 0.5f, virtualWindowSizeY * 0.6f); }

    // Exit button, and its absolute parameter, which is managed by CPageBeginning, not CVisualTexture.
    CVisualTexture exitButtonTexture;
    sf::Vector2f updateExitTexturePosition() const { return sf::Vector2f(virtualWindowSizeX * 0.03f, virtualWindowSizeX * 0.03f); }
    sf::Vector2f updateExitTextureSize() const { return sf::Vector2f(virtualWindowSizeX / 1920.f * 50.f, virtualWindowSizeX / 1920.f * 50.f); }

    CVisualTexture exitButtonTextureHover;

    // Exit button text when hover.
    CVisualText exitButtonText;
    int updateExitTextSize() const { return std::min(virtualWindowSizeX / 1920.f * 30.f, virtualWindowSizeY / 1080.f * 30.f); }
    sf::Vector2f updateExitTextPosition() const { return sf::Vector2f(virtualWindowSizeX * 0.03f + exitButtonTexture.area.width, virtualWindowSizeX * 0.03f); }
    // Exit button text's y position equals to exit button texture's y position.
};

