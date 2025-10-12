// PageGame.hpp
/*
    The game page.
*/

#pragma once

#include "Page.hpp"
#include "visualize.hpp"
#include "blocks.hpp"

#define returnButtonX 50
#define returnButtonY 50
#define returnButtonSize 50
#define returnButtonArea MAKE_AREA_SQUARE(returnButtonX, returnButtonY, returnButtonSize)

#define restartButtonX VIRTUAL_WINDOW_SIZE_X  - 50
#define restartButtonY 50
#define restartButtonSize 50
#define restartButtonArea MAKE_AREA_SQUARE(restartButtonX, restartButtonY, restartButtonSize)



class CPageGame : public CPage
{
public:
    // See the comments in Page.hpp for the function's functionality.
    void handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages) override;
    void update(sf::RenderWindow &window, sf::Event event) override;
    void render(sf::RenderWindow &window, sf::Event event) override;
    bool getIsInGame() { return isInGame; }
    bool getIsInitialized() { return isInitialized; }
    // Game start state.
    void setGameStart(bool gameStart) { isGameStart = gameStart; }
    // Check if game finished
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
    std::map<std::string, sf::Texture> functionButtonTexture;
};

// Get clicked block position.
sf::Vector2i getClickedBlockPosition(sf::RenderWindow &window, const sf::Event &event, const sf::FloatRect &boardBounds, int blockSize, int rows, int cols);
