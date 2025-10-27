#include "../include/PageGame.hpp"

// Handle event for the game page.
void CPageGame::handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    // Handle key event.
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            backToBeginning(window, currentPage, pages);
        }
    }

    // Handle the text input event.
    if (event.type == sf::Event::TextEntered)
    {
        if (customMapInputBox_X.isActive())
        {
            customMapInputBox_X.handleEvent(event);
        }
        else if (customMapInputBox_Y.isActive())
        {
            customMapInputBox_Y.handleEvent(event);
        }
        else if (customMapInputBox_Mine.isActive())
        {
            customMapInputBox_Mine.handleEvent(event);
        }
    }

    // Handle mouse event
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (isInGame == false) // If game is not in progress, handle menu event.
        {
            if (isCustomizingMap == false) // If not customizing map, handle difficulty selection.
            {
                if (isMouseClickInArea(window, event, difficultyEasy.textObject.getGlobalBounds()))
                {
                    difficultyChosen = DIFFICULTY_EASY;
                    isMapDefined = true;
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Easy' button clicked." << endl;
                }
                else if (isMouseClickInArea(window, event, difficultyMedium.textObject.getGlobalBounds()))
                {
                    difficultyChosen = DIFFICULTY_MEDIUM;
                    isMapDefined = true;
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Medium' button clicked." << endl;
                }
                else if (isMouseClickInArea(window, event, difficultyHard.textObject.getGlobalBounds()))
                {
                    difficultyChosen = DIFFICULTY_HARD;
                    isMapDefined = true;
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Hard' button clicked." << endl;
                }
                else if (isMouseClickInArea(window, event, customMap.textObject.getGlobalBounds()))
                {
                    isCustomizingMap = true;
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Customize' button clicked." << endl;
                }
            }
            else // If customizing map, handle costomizing page.
            {
                if (isMouseClickInArea(window, event, comfirmCustomMap.textObject.getGlobalBounds()))
                {
                    if (customMapInputBox_X.getText() != "" && customMapInputBox_Y.getText() != "")
                    {
                        try // Try to get input from custom map input box.
                        {
                            // Check if input for custom map size X and Y is valid.
                            if (customMapInputBox_X.getText() != "" && !isStringAllNum(customMapInputBox_X.getText()))
                            {
                                cout << "\33[31m[ERROR]\33[0m (In CPageGame::handleEvent) Invalid input for custom map size X." << endl;
                                return;
                            }
                            if (customMapInputBox_Y.getText() != "" && !isStringAllNum(customMapInputBox_Y.getText()))
                            {
                                cout << "\33[31m[ERROR]\33[0m (In CPageGame::handleEvent) Invalid input for custom map size Y." << endl;
                                return;
                            }
                            if (customMapInputBox_Mine.getText() != "" && !isStringAllNum(customMapInputBox_Mine.getText()))
                            {
                                cout << "\33[31m[ERROR]\33[0m (In CPageGame::handleEvent) Invalid input for custom map mine count." << endl;
                                return;
                            }

                            CustomSizeX = std::stoi(customMapInputBox_X.getText());
                            CustomSizeY = std::stoi(customMapInputBox_Y.getText());
                            CustomMines = std::stoi(customMapInputBox_Mine.getText());

                            if (CustomMines <= 0 || CustomMines >= CustomSizeX * CustomSizeY) // Next check if mines count input is larger than 0 and smaller than sizeX * sizeY.
                            {
                                cout << "\33[31m[ERROR]\33[0m (In CPageGame::handleEvent) Invalid input for custom map mine count." << endl;
                                return;
                            }
                        }
                        catch (const std::invalid_argument &e) // If detect invalid argument, output error message and do nothing.
                        {
                            cout << "\33[31m[ERROR]\33[0m (In CPageGame::handleEvent) " << e.what() << endl;
                            CustomSizeX = -1;
                            CustomSizeY = -1;
                            CustomMines = -1;
                            // Do not return and keep processing until output click info.
                        }

                        if (CustomSizeX > 0 && CustomSizeY > 0 && CustomSizeX <= 100 && CustomSizeY <= 100)
                        { // New judgement await to implement. ( && CustomMines > 0 && CustomMines < CustomSizeX * CustomSizeY)
                            // Check if input is valid. If so, update specific bool parameter.
                            isCustomizingMap = false;
                            difficultyChosen = DIFFICULTY_CUSTOM; // Set difficulty chosen to custom.

                            // Set game board's size and output info.
                            gameBoard.setMapSizeAndMines(CustomSizeX, CustomSizeY, CustomMines);
                            cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " Custom map size set to " << CustomSizeX << " " << CustomSizeY << " with " << CustomMines << " mines." << endl;

                            isMapDefined = true; // Finally set map defined to true.
                        }
                        else
                        {
                            // If input is invalid, output error message.
                            cout << "\33[31m[ERROR]\33[0m Invalid input: " << CustomSizeX << " " << CustomSizeY << " with " << CustomMines << " mines." << endl;
                        }
                    }
                    else
                    {
                        // If every input boxs are empty, output error message.
                        cout << "\33[31m[ERROR]\33[0m Empty input in customMapInputBox_X, customMapInputBox_Y and costomMapInputBox_Mines." << endl;
                    }
                    // Output info message whatever the result.
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Confirm' button clicked." << endl;
                }
                else if (isMouseClickInArea(window, event, backToDifficulty.textObject.getGlobalBounds()))
                {
                    // If click 'Back to difficulty' button, set customizing map to false and return to difficulty select.
                    isCustomizingMap = false;
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Cancel' button clicked." << endl;
                }
                else if (isMouseClickInArea(window, event, customMapInputBox_X.getGlobalBounds()))
                {
                    // If click 'customMapInputBox_X' input bar, set it active and deactivate 'customMapInputBox_Y'.
                    customMapInputBox_X.setActive(true);
                    customMapInputBox_Y.setActive(false);
                    customMapInputBox_Mine.setActive(false);
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'customMapInputBox_X' input bar clicked." << endl;
                }
                else if (isMouseClickInArea(window, event, customMapInputBox_Y.getGlobalBounds()))
                {
                    // If click 'customMapInputBox_Y' input bar, set it active and deactivate 'customMapInputBox_X'.
                    customMapInputBox_Y.setActive(true);
                    customMapInputBox_X.setActive(false);
                    customMapInputBox_Mine.setActive(false);
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'customMapInputBox_Y' input bar clicked." << endl;
                }
                else if (isMouseClickInArea(window, event, customMapInputBox_Mine.getGlobalBounds()))
                {
                    // If click 'customMapInputBox_Mine' input bar, set it active and deactivate other input bars.
                    customMapInputBox_Mine.setActive(true);
                    customMapInputBox_X.setActive(false);
                    customMapInputBox_Y.setActive(false);
                    cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'customMapInputBox_Mine' input bar clicked." << endl;
                }
                else 
                {
                    // If click outside all interactive visual elements, deactivate both input bars and do nothing.
                    customMapInputBox_X.setActive(false);
                    customMapInputBox_Y.setActive(false);
                    customMapInputBox_Mine.setActive(false);
                }
            }
            
        }
        else // If game is in progress, handle game event.
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
        else if (isMouseClickInArea(window, event, backToChooseDifficultyButton.area))
        {
            // Back to choose difficulty button clicked.
            // Reset all relevant parameters.
            isMapDefined = false;
            isCustomizingMap = false;
            isInGame = false;
            isGameOver = false;
            isInitialized = false;
            difficultyChosen = NONE;
            gameBoard.reset();

            cout << "\33[34m[INFO]\33[0m " << getPageName(GAME_PAGE) << " 'Back to choose difficulty' button clicked." << endl;
        }
        else
            ; // Clicked outside function buttons, do nothing.
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

        /* Resident elements */
        // Update the position of the function buttons.
        returnButton.updateWhenWindowResize(updateReturnButtonPosition(), updateReturnButtonSize());
        restartButton.updateWhenWindowResize(updateRestartButtonPosition(), updateRestartButtonSize());
        backToChooseDifficultyButton.updateWhenWindowResize(updateBackToChooseDifficultyButtonPosition(), updateBackToChooseDifficultyButtonSize());

        /* Difficulty selection */
        // Update notification text.
        notificationToPlayer.updateWhenWindowResize(updateNotificationToPlayerPosition());
        // Update difficulty buttons.
        difficultyEasy.updateWhenWindowResize(updateDifficultyEasyPosition());
        difficultyMedium.updateWhenWindowResize(updateDifficultyMediumPosition());
        difficultyHard.updateWhenWindowResize(updateDifficultyHardPosition());
        customMap.updateWhenWindowResize(updateCustomMapPosition());

        /* Map customize */
        // Update custom map input box.
        customMapInputBox_X.updateWhenWindowResize(updateCustomMapInputBox_XPosition(), updateCustomMapInputBox_XSize(), updateCustomMapInputBox_XFontSize());
        customMapInputBox_Y.updateWhenWindowResize(updateCustomMapInputBox_YPosition(), updateCustomMapInputBox_YSize(), updateCustomMapInputBox_YFontSize());
        customMapInputBox_Mine.updateWhenWindowResize(updateCustomMapInputBox_MinePosition(), updateCustomMapInputBox_MineSize(), updateCustomMapInputBox_MineFontSize());

        // Update custom map confirm button.
        comfirmCustomMap.updateWhenWindowResize(updateComfirmCustomMapPosition());
        // Update back to difficulty selection text botton.
        backToDifficulty.updateWhenWindowResize(updateBackToDifficultyPosition());

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
        

        if (isCustomizingMap == false)
        {
            // Render difficulty: Easy buttons.
            if (isMouseStayInArea(window, event, difficultyEasy.textObject.getGlobalBounds()))
                difficultyEasy.textObject.setScale(1.1f, 1.1f);
            else
                difficultyEasy.textObject.setScale(1.f, 1.f);
            drawText(window, difficultyEasy);

            // Render difficulty: Medium buttons.
            if (isMouseStayInArea(window, event, difficultyMedium.textObject.getGlobalBounds()))
                difficultyMedium.textObject.setScale(1.1f, 1.1f);
            else
                difficultyMedium.textObject.setScale(1.f, 1.f);
            drawText(window, difficultyMedium);

            // Render difficulty: Hard buttons.
            if (isMouseStayInArea(window, event, difficultyHard.textObject.getGlobalBounds()))
                difficultyHard.textObject.setScale(1.1f, 1.1f);
            else
                difficultyHard.textObject.setScale(1.f, 1.f);
            drawText(window, difficultyHard);

            // Customize map.
            if (isMouseStayInArea(window, event, customMap.textObject.getGlobalBounds()))
                customMap.textObject.setScale(1.1f, 1.1f);
            else
                customMap.textObject.setScale(1.f, 1.f);
            drawText(window, customMap);
        }
        else if (isCustomizingMap == true)
        {
            // Input box. (X, Y)
            customMapInputBox_X.draw(window);
            customMapInputBox_Y.draw(window);
            customMapInputBox_Mine.draw(window);

            // Confirm button.
            if (isMouseStayInArea(window, event, comfirmCustomMap.textObject.getGlobalBounds()))
                comfirmCustomMap.textObject.setScale(1.1f, 1.1f);
            else
                comfirmCustomMap.textObject.setScale(1.f, 1.f);
            drawText(window, comfirmCustomMap);

            // Back to difficulty selection.
            if (isMouseStayInArea(window, event, backToDifficulty.textObject.getGlobalBounds()))
                backToDifficulty.textObject.setScale(1.1f, 1.1f);
            else
                backToDifficulty.textObject.setScale(1.f, 1.f);
            drawText(window, backToDifficulty);
        }
    }
    else
    {
        // Render the game.
        if ((isInGame == true || isGameOver == true) && isMapDefined == true)
        {
            // render game board.
            gameBoard.render(window, event);
        }

        // Render the restart button.
        if (isMouseStayInArea(window, event, restartButton.area))
            restartButton.scale = 1.1f;
        else
            restartButton.scale = 1.f;
        drawCachedTexture(window, restartButton, functionButtonTexture);

        // Render the back to choose difficulty button.
        if (isMouseStayInArea(window, event, backToChooseDifficultyButton.area))
            backToChooseDifficultyButton.scale = 1.1f;
        else
            backToChooseDifficultyButton.scale = 1.f;
        drawCachedTexture(window, backToChooseDifficultyButton, functionButtonTexture);
    }

    // Render the return button.
    if (isMouseStayInArea(window, event, returnButton.area))
        returnButton.scale = 1.1f;
    else
        returnButton.scale = 1.f;
    drawCachedTexture(window, returnButton, functionButtonTexture);
}

// Back to beginning page.
void CPageGame::backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    changePage(window, currentPage, BEGINNING_PAGE, pages);
    // Clear texture cache.
    freeFunctionButtonTexture();
    gameBoard.freeGameBoardTexture();
    
    // Set all parameter false.
    difficultyChosen = NONE;
    isMapDefined = false;
    isCustomizingMap = false;
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
    preloadTexture("page_game/backtochoose.png", functionButtonTexture);
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
    case DIFFICULTY_CUSTOM:
        gameBoard.initialize(CustomSizeX, CustomSizeY, CustomMines);
        break;
    default:
        break;
    }
};