#include "../include/PageGame.hpp"

void CPageGame::handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            backToBeginning(window, currentPage, pages);
        }
    }
}

void CPageGame::update(sf::RenderWindow &window)
{
    // If the game start, update the animation.
    if (isGameStart == true)
    {
        gameBoard.initialize();
        isGameStart = false;
        isInitialized = true;
        isInGame = true;

        // Preload textures.
        // preloadTexture("block.png");
        preloadTexture("page_game/mine.png");
        // preloadTexture("flag.png");
        // preloadTexture("number.png");
    }

    // If the game is in progress, update the game board.
    if (isInGame == true)
    {
        gameBoard.update();
        gameBoard.render(window);
    }
}

void CPageGame::render(sf::RenderWindow &window)
{
    // Render the game.
    if (isInitialized == true && isInGame == true)
    {
        gameBoard.render(window);
    }
}

void CPageGame::backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    changePage(window, currentPage, BEGINNING_PAGE, pages);
    // Clear texture cache.
    clearTextureCache();
    cout << "\33[34m[INFO]\33[0m Texture cache cleared." << endl;
    
    isGameStart = false;
    isInitialized = false;
    isInGame = false;
}
