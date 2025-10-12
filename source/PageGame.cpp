#include "../include/PageGame.hpp"

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
        sf::Vector2i clickedBlock = getClickedBlockPosition(window, event, gameBoard.getBoardArea(), gameBoard.getBlockSize(), gameBoard.getBoardSizeX(), gameBoard.getBoardSizeY());
        if (event.mouseButton.button == sf::Mouse::Left && isInGame == true)
        {
            // Left click.
            if (clickedBlock.x != -1 && clickedBlock.y != -1 && 
                gameBoard.isBlockRevealed(clickedBlock.x, clickedBlock.y) == false && 
                gameBoard.isBlockFlagged(clickedBlock.x, clickedBlock.y) == false)
            {
                // If the clicked block is a mine, game over.
                if (gameBoard.getBlockType(clickedBlock.x, clickedBlock.y) == MINE)
                {
                    gameBoard.revealAllMines();
                    isInGame = false;
                    isGameOver = true;
                }
                // If the clicked block is empty, reveal nearby safe blocks.
                else if (gameBoard.getBlockType(clickedBlock.x, clickedBlock.y) == EMPTY)
                {
                    gameBoard.revealNearbySafeBlock(clickedBlock.x, clickedBlock.y);
                }
                // If the clicked block is a number, just reveal it.
                else
                {
                    // If the clicked block is not empty, set the mine count around.
                    gameBoard.setMineCountAroundForBlock(clickedBlock.x, clickedBlock.y);
                    // Reveal the block.
                    gameBoard.revealBlock(clickedBlock.x, clickedBlock.y);
                }
                
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Right && isInGame == true)
        {
            // Right click.
            if (clickedBlock.x != -1 && clickedBlock.y != -1 && 
                gameBoard.isBlockRevealed(clickedBlock.x, clickedBlock.y) == false)
            {
                // If the clicked block is not flagged, flag it.
                if (gameBoard.isBlockFlagged(clickedBlock.x, clickedBlock.y) == false)
                {
                    gameBoard.setBlockFlagged(clickedBlock.x, clickedBlock.y, true);
                }
                // If the clicked block is flagged, unflag it.
                else
                {
                    gameBoard.setBlockFlagged(clickedBlock.x, clickedBlock.y, false);
                }
            }
        }
        cout << "Revealed block counts: " << gameBoard.getRevealedBlocksCount() << endl;

        if (isMouseClickInArea(window, event, returnButtonArea))
        {
            backToBeginning(window, currentPage, pages);
        }
        else if (isMouseClickInArea(window, event, restartButtonArea))
        {
            restartGame();
        }
    }
}

void CPageGame::update(sf::RenderWindow &window, sf::Event event)
{
    // If the game start, update the animation.
    if (isGameStart == true)
    {
        gameBoard.initialize();
        isGameStart = false;
        isInitialized = true;
        isInGame = true;

        // Preload textures.
        preloadFunctionButtonTexture();
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
}

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
    drawCachedTexture(window, returnButtonX, returnButtonY, returnButtonSize, "page_game/return.png", functionButtonTexture);
    // Render the restart button.
    drawCachedTexture(window, restartButtonX, restartButtonY, restartButtonSize, "page_game/restart.png", functionButtonTexture);
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
}

// Returns the grid position (column, row) of the block that was clicked by the mouse.
// Only responds to left mouse button clicks within the board boundaries.
sf::Vector2i getClickedBlockPosition(sf::RenderWindow &window, const sf::Event &event, const sf::FloatRect &boardBounds, int blockSize, int rows, int cols)
{
    // Check if the event is a left mouse button press
    if (event.type != sf::Event::MouseButtonPressed)
        return sf::Vector2i(-1, -1); // Invalid click, return sentinel value

    // Get the mouse position relative to the window
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

    // Convert pixel coordinates to world coordinates (accounts for view transformations)
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    // Calculate the block indices based on block size
    int col = static_cast<int>(worldPos.x - boardBounds.left) / blockSize;
    int row = static_cast<int>(worldPos.y - boardBounds.top) / blockSize;

    // Check if the calculated position is within the board boundaries
    if (col < 0 || col >= cols || row < 0 || row >= rows)
        return sf::Vector2i(-1, -1); // Click outside the board

    // Debug Output
    // if (event.mouseButton.button == sf::Mouse::Left)
    //     cout << "\033[34m[INFO]\033[0m Left clicked block position: (" << col << ", " << row << ")" << endl;
    // else if (event.mouseButton.button == sf::Mouse::Right)
    //     cout << "\033[34m[INFO]\033[0m Right clicked block position: (" << col << ", " << row << ")" << endl;

    // Return the valid block position
    return sf::Vector2i(col, row);
}

void CPageGame::preloadFunctionButtonTexture()
{
    preloadTexture("page_game/return.png", functionButtonTexture);
    preloadTexture("page_game/restart.png", functionButtonTexture);
}

void CPageGame::freeFunctionButtonTexture()
{
    freePreloadTextureCache(functionButtonTexture);
}