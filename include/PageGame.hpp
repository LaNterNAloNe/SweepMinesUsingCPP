// PageGame.hpp
/*
    The game page.
*/

#pragma once

#include "Page.hpp"
#include "visualize.hpp"
#include "blocks.hpp"
#include "debug.hpp"

// #define returnButtonX 50
// #define returnButtonY 50
// #define returnButtonSize 50
// #define returnButtonArea makeSquareArea(returnButtonX, returnButtonY, returnButtonSize)

// #define restartButtonX virtualWindowSizeX  - 50
// #define restartButtonY 50
// #define restartButtonSize 50
// #define restartButtonArea makeSquareArea(restartButtonX, restartButtonY, restartButtonSize)



class CPageGame : public CPage
{
public:
    CPageGame() : returnButton("page_game/return.png", updateReturnButtonPosition(), updateReturnButtonSize()),
                  restartButton("page_game/restart.png", updateRestartButtonPosition(), updateRestartButtonSize()) {}
    // See the comments in Page.hpp for the function's functionality.
    void handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages) override;
    void update(sf::RenderWindow &window, sf::Event event) override;
    void render(sf::RenderWindow &window, sf::Event event) override;
    bool getIsInGame() { return isInGame; }
    bool getIsInitialized() { return isInitialized; }
    // Game start state.
    void setGameStart(bool gameStart) { isGameStart = gameStart; }
    // Check if game finished

    // Check if game finished.
    bool checkIsTextureLoaded() { return isTextureLoaded; };
    ~CPageGame() override {}
private:
    // Back to beginning page.
    void backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages);
    void restartGame();

    // Load and free texture cache
    void preloadFunctionButtonTexture();
    void freeFunctionButtonTexture();

    // Game board.
    CGameBoard gameBoard;

    // Game parameter
    // Game start state.
    bool isGameStart = true;
    bool isInitialized = false;
    bool isInGame = false;
    bool isGameOver = false;

    // Texture cache.
    TextureCache functionButtonTexture;
    bool isTextureLoaded = false;

    CVisualTexture returnButton;
    sf::Vector2f updateReturnButtonPosition() { return sf::Vector2f(virtualWindowSizeX * 0.03f, virtualWindowSizeX * 0.03f); }
    sf::Vector2f updateReturnButtonSize() { return sf::Vector2f(virtualWindowSizeX / 1920.f * 50.f, virtualWindowSizeX / 1920.f * 50.f); }

    CVisualTexture restartButton;
    sf::Vector2f updateRestartButtonPosition() { return sf::Vector2f(virtualWindowSizeX - virtualWindowSizeX * 0.03f, virtualWindowSizeX * 0.03f); }
    sf::Vector2f updateRestartButtonSize() { return sf::Vector2f(virtualWindowSizeX / 1920.f * 50.f, virtualWindowSizeX / 1920.f * 50.f); }
};
