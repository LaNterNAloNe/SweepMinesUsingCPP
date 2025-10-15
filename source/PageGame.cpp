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
        if (isMouseClickInArea(window, event, difficultyEasy.area) && isInGame == false)
        {
            difficultyChosen = DIFFICULTY_EASY;
            isMapDefined = true;
            cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Easy' button clicked." << endl;
        }
        else if (isMouseClickInArea(window, event, difficultyMedium.area) && isInGame == false)
        {
            difficultyChosen = DIFFICULTY_MEDIUM;
            isMapDefined = true;
            cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Medium' button clicked." << endl;
        }
        else if (isMouseClickInArea(window, event, difficultyHard.area) && isInGame == false)
        {
            difficultyChosen = DIFFICULTY_HARD;
            isMapDefined = true;
            cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Hard' button clicked." << endl;
        }
        else if (isInGame)
        {
            gameBoard.handleEvent(window, event);
        }

        if (isMouseClickInArea(window, event, returnButton.area))
        {
            backToBeginning(window, currentPage, pages);
            cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Return' button clicked." << endl;
        }
        else if (isMouseClickInArea(window, event, restartButton.area))
        {
            restartGame();
            cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Restart' button clicked." << endl;
        }
    }
}

// Update the game page.
void CPageGame::update(sf::RenderWindow &window, sf::Event event)
{
    // If map is defined and game is not started, start the game.
    if (isMapDefined == true && isInitialized == false && isInGame == false)
    {
        cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " game started." << endl;
        startGame(difficultyChosen);
        isInitialized = true;
        isInGame = true;
    }

    // If the game is in progress, update the game board.
    if (isInGame == true)
    {
        gameBoard.update();
    }

    // If game is in progress and detect game finished, set game over, only be triggerred when isInGame = true.
    if (gameBoard.isGameFinished() && isInGame == true)
    {
        cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " game finished." << endl;
        isInGame = false;
        isGameOver = true;
    }

    // Check if texture preloaded.
    if (!gameBoard.checkIfTextureLoaded())
        gameBoard.preloadGameBoardTexture();
    if (!checkIsTextureLoaded())
        preloadFunctionButtonTexture();

    if (event.type == sf::Event::Resized || lastWindowSize != static_cast<sf::Vector2f>(window.getSize()))
    {
        // Update the lastWindowSize parameter in this page class.
        lastWindowSize = static_cast<sf::Vector2f>(window.getSize());

        // Update the position of the function buttons.
        returnButton.updateWhenWindowResize(updateReturnButtonPosition(), updateReturnButtonSize());
        restartButton.updateWhenWindowResize(updateRestartButtonPosition(), updateRestartButtonSize());

        // Update notification text.
        notificationToPlayer.updateWhenWindowResize(updateNotificationToPlayerPosition());
        // Update difficulty buttons.
        difficultyEasy.updateWhenWindowResize(updateDifficultyEasyPosition());
        difficultyMedium.updateWhenWindowResize(updateDifficultyMediumPosition());
        difficultyHard.updateWhenWindowResize(updateDifficultyHardPosition());

        // Update gameboard's area and blocks' visual parameter if game is initialized.
        if (isInitialized == true)
        {
            gameBoard.updateBoardAndBlockVisualization();
        }
    }
}

// Draw the game page.
void CPageGame::render(sf::RenderWindow &window, sf::Event event)
{
    // Draw white background.
    drawRectangle(window, 0, 0, WindowSizeX, WindowSizeY, sf::Color::White);

    // Select difficulty or customize map
    if (isMapDefined == false)
    {
        // Render difficulty selection.
        // Render notification text.
        drawText(window, notificationToPlayer);
        // Render difficulty buttons.
        if (isMouseStayInArea(window, event, difficultyEasy.area))
            difficultyEasy.textObject.setScale(1.1f, 1.1f);
        else
            difficultyEasy.textObject.setScale(1.f, 1.f);
        drawText(window, difficultyEasy);

        if (isMouseStayInArea(window, event, difficultyMedium.area))
            difficultyMedium.textObject.setScale(1.1f, 1.1f);
        else
            difficultyMedium.textObject.setScale(1.f, 1.f);
        drawText(window, difficultyMedium);

        if (isMouseStayInArea(window, event, difficultyHard.area))
            difficultyHard.textObject.setScale(1.1f, 1.1f);
        else
            difficultyHard.textObject.setScale(1.f, 1.f);
        drawText(window, difficultyHard);
    }
    else
    {
        // Render the game.
        if ((isInGame == true || isGameOver == true) && isMapDefined == true)
        {
            // render game board.
            gameBoard.render(window, event);
        }
    }

    // Render the return button.
    if (isMouseStayInArea(window, event, returnButton.area))
        returnButton.scale = 1.1f;
    else
        returnButton.scale = 1.f;
    drawCachedTexture(window, returnButton, functionButtonTexture);
    // Render the restart button.
    if (isMouseStayInArea(window, event, restartButton.area))
        restartButton.scale = 1.1f;
    else
        restartButton.scale = 1.f;
    drawCachedTexture(window, restartButton, functionButtonTexture);
}

// Back to beginning page.
void CPageGame::backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    changePage(window, currentPage, BEGINNING_PAGE, pages);
    // Clear texture cache.
    freeFunctionButtonTexture();
    gameBoard.freeGameBoardTexture();
    cout << "\33[34m[INFO]\33[0m Texture cache cleared." << endl;
    
    // Set all parameter false.
    difficultyChosen = NONE;
    isMapDefined = false;
    isInitialized = false;
    isInGame = false;
    isGameOver = false;
    gameBoard.reset();
}

// Restart the game.
void CPageGame::restartGame()
{
    // Here we think that map is defined and just need to reinitialize the game board.
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

// Start game.
void CPageGame::startGame(int difficulty)
{
    isInGame = true;
    isMapDefined = true;

    switch (difficulty)
    {
    case DIFFICULTY_EASY:
        gameBoard.initialize(10, 10, 10);
        break;
    case DIFFICULTY_MEDIUM:
        gameBoard.initialize(15, 15, 40);
        break;
    case DIFFICULTY_HARD:
        gameBoard.initialize(30, 20, 100);
        break;
    default:
        break;
    }
};