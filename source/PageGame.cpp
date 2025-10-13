#include "../include/PageGame.hpp"

// Handle event for the game page.
void CPageGame::handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    // Handle key event
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            backToBeginning(window, currentPage, pages);
        }
    }
    // Handle mouse event
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (isInGame)
        {
            gameBoard.handleEvent(window, event);
        }
        

        cout << "Revealed block counts: " << gameBoard.getRevealedBlocksCount() << endl;

        if (isMouseClickInArea(window, event, returnButtonArea))
        {
            backToBeginning(window, currentPage, pages);
            cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Return' button clicked." << endl;
        }
        else if (isMouseClickInArea(window, event, restartButtonArea))
        {
            restartGame();
            cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Restart' button clicked." << endl;
        }
    }
}

// Update the game page.
void CPageGame::update(sf::RenderWindow &window, sf::Event event)
{
    // If the game start, update the animation.
    if (isGameStart == true)
    {
        gameBoard.initialize();
        isGameStart = false;
        isInitialized = true;
        isInGame = true;
    }

    // If the game is in progress, update the game board.
    if (isInGame == true)
    {
        gameBoard.update();
    }

    // Check if game finished
    if (gameBoard.isGameFinished())
    {
        isInGame = false;
        isGameOver = true;
    }

    // Check if texture preloaded.
    if (!gameBoard.checkIfTextureLoaded())
        gameBoard.preloadGameBoardTexture();
    if (!checkIsTextureLoaded())
        preloadFunctionButtonTexture();
}

// Draw the game page.
void CPageGame::render(sf::RenderWindow &window, sf::Event event)
{
    // Draw white background.
    drawRectangle(window, 0, 0, VIRTUAL_WINDOW_SIZE_X, VIRTUAL_WINDOW_SIZE_Y, sf::Color::White);

    // Render the game.
    if (isInGame == true || isGameOver == true)
    {
        // render game board.
        gameBoard.render(window, event);
    }

    // Render the return button.
    drawCachedTexture(window, returnButtonX, returnButtonY, 
        isMouseStayInArea(window, event, returnButtonArea) ? returnButtonSize * 1.1 : returnButtonSize, "page_game/return.png", functionButtonTexture);
    // Render the restart button.
    drawCachedTexture(window, restartButtonX, restartButtonY, 
        isMouseStayInArea(window, event, restartButtonArea) ? restartButtonSize * 1.1 : restartButtonSize, "page_game/restart.png", functionButtonTexture);
}

// Back to beginning page.
void CPageGame::backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    changePage(window, currentPage, BEGINNING_PAGE, pages);
    // Clear texture cache.
    freeFunctionButtonTexture();
    gameBoard.freeGameBoardTexture();
    cout << "\33[34m[INFO]\33[0m Texture cache cleared." << endl;
    
    isGameStart = true;
    isInitialized = false;
    isInGame = false;
    isGameOver = false;
    gameBoard.reset();
}

// Restart the game.
void CPageGame::restartGame()
{
    isGameStart = true;
    isInitialized = false;
    isInGame = false;
    isGameOver = false;
    gameBoard.reset();

    cout << "\33[34m[INFO]\33[0m Game restarted." << endl;
}

// Preload function button texture.
void CPageGame::preloadFunctionButtonTexture()
{
    preloadTexture("page_game/return.png", functionButtonTexture);
    preloadTexture("page_game/restart.png", functionButtonTexture);
    isTextureLoaded = true;
}

// Free function button texture.
void CPageGame::freeFunctionButtonTexture()
{
    freePreloadTextureCache(functionButtonTexture);
    isTextureLoaded = false;
}