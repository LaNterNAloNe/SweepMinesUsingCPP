#include "../include/blocks.hpp"

/* CSafeBlock class implementation */
void CSafeBlock::setMineCountAround(int count, int x, int y, int boardSizeX, int boardSizeY)
{
    // Set the mine count around for this block.
    if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY && count >= 0)
    {
        if (count == 0) 
        {
            type = EMPTY;
        }
        else 
        {
            type = NUMBER;
        }
        mineCoutAround = count;
    } else {
        cout << "\33[31m[ERROR]\33[0m Invalid position: (" << x << ", " << y << "). (Board Size: " << boardSizeX << ", " << boardSizeY << ")" << "or mine count to pass:" << count << " (In function CSafeBlock::setMineCountAround)" << endl;
    }
}



/* CGameBoard class implementation */

// Handle game event.
void CGameBoard::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    // Wait for transplant
    sf::Vector2i clickedBlock = getClickedBlockPosition(window, event, getBoardArea(), getBlockSize());

    cout << "Clicked block: (" << clickedBlock.x << ", " << clickedBlock.y << ")" << endl;

    // Return if get invalid clicked block coordinate.
    if (clickedBlock.x == -1 || clickedBlock.y == -1)
    {
        return;
    }

    // If the clicked block is valid, handle the event.
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        // Left click.
        // If the clicked block is not revealed and not flagged, try to reveal and handle it.
        if (isBlockRevealed(clickedBlock.x, clickedBlock.y) == false &&
            isBlockFlagged(clickedBlock.x, clickedBlock.y) == false)
        {
            if (getBlockType(clickedBlock.x, clickedBlock.y) == EMPTY)
            {
                revealAroundSafeBlock(clickedBlock.x, clickedBlock.y);
            }
            // If the clicked block is a number, just reveal it.
            else
            {
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // If it's the first click and it's a mine or number block, replace surrounding mines to other non-mine blocks.
                // (Only enabled when option: Use Win7 MineSweeper Feature is on)
                if (globalSettings.useWin7MineSweeperFeature && gameStatus == NONE && revealedBlocksCount == 0 &&
                    (getBlockType(clickedBlock.x, clickedBlock.y) == MINE || getBlockType(clickedBlock.x, clickedBlock.y) == NUMBER))
                {
                    // replaceMinesAroundToMapRandomly(clickedBlock.x, clickedBlock.y); // To be implemented.
                } 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                // If the clicked block is not empty, set the mine count around.
                setMineCountAroundForBlock(clickedBlock.x, clickedBlock.y);
                // Reveal the block.
                revealBlock(clickedBlock.x, clickedBlock.y);
            }
        }
        // If the clicked block is already revealed, try to judge that if unrevealed mines are flagged, 
        // if so, reveal nearby safe blocks.
        else if (isBlockRevealed(clickedBlock.x, clickedBlock.y) == true)
        {
            // If the clicked block is a number, check if the number of flagged blocks around is equal to the mine count around.
            if (getBlockType(clickedBlock.x, clickedBlock.y) == NUMBER)
            {
                revealBlocksNearbyIfNearbyFlagsEqualNum(clickedBlock.x, clickedBlock.y);
            }
        }
    }
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
        // Right click.
        if (isBlockRevealed(clickedBlock.x, clickedBlock.y) == false)
        {
            // If the clicked block is not flagged, flag it.
            if (isBlockFlagged(clickedBlock.x, clickedBlock.y) == false)
            {
                setBlockFlagged(clickedBlock.x, clickedBlock.y, true);
            }
            // If the clicked block is flagged, unflag it.
            else
            {
                setBlockFlagged(clickedBlock.x, clickedBlock.y, false);
            }
        }
    }
}

void CGameBoard::update()
{
    if (revealedBlocksCount == (boardSizeX * boardSizeY - mineCount) && gameStatus != MINE_REVEALED)
    {
        gameStatus = WON;
        isGameWon = true;
        revealAllMineBlocks();
        cout << "\33[34m[INFO]\33[0m Game \033[32mWon.\033[0m" << endl;
    } 
    else if (gameStatus == MINE_REVEALED)
    {
        gameStatus = LOST;
        isGameLost = true;
        revealAllMineBlocks();
        cout << "\33[34m[Info]\33[0m Game \033[31mlost.\033[0m" << endl;
    } 
}

void CGameBoard::render(sf::RenderWindow &window, sf::Event &event)
{
    // According to global setting to decide which theme to use.
    std::string theme = transformThemeToTextureThemePath(globalSettings.theme);

    // Render the game board, using cached texture. (Must)
    for (int i = 0; i < boardSizeX; ++i)
    {
        for (int j = 0; j < boardSizeY; ++j)
        {
            sf::FloatRect blockPosition = blocks[i][j]->getPosition();

            // Draw the block if it is not revealed.
            if (blocks[i][j]->isRevealed() == false)
            {
                // If the block is not revealed and not flagged, draw the common texture.
                if (isMouseStayInArea(window, event, blockPosition) && !blocks[i][j]->isFlagged() && globalSettings.theme != CLASSICAL)
                {
                    // If the block is not flagged and not hovered, draw the common texture.
                    blocks[i][j]->blockTexture.path = "page_game/" + theme + "block_hover.png";
                    drawCachedTexture(window, blocks[i][j]->blockTexture, gameBoardTexture);
                }
                else if (!isMouseStayInArea(window, event, blockPosition) && !blocks[i][j]->isFlagged())
                {
                    // If the block is not flagged and hovered, draw the hover texture.
                    blocks[i][j]->blockTexture.path = "page_game/" + theme + "block.png";
                    drawCachedTexture(window, blocks[i][j]->blockTexture, gameBoardTexture);
                }
                // If the block is flagged, draw the flagged texture.
                else if (blocks[i][j]->isFlagged())
                {
                    // If the block is flagged, draw the flagged texture.
                    blocks[i][j]->blockTexture.path = "page_game/" + theme + "flag.png";
                    drawCachedTexture(window, blocks[i][j]->blockTexture, gameBoardTexture);
                }
                else 
                {
                    // If the block is not flagged and not hovered, draw the common texture.
                    blocks[i][j]->blockTexture.path = "page_game/" + theme + "block.png";
                    drawCachedTexture(window, blocks[i][j]->blockTexture, gameBoardTexture);
                }
            }

            // Draw the block if it is revealed.
            if (blocks[i][j]->isRevealed())
            {
                if (blocks[i][j]->getType() == MINE)
                {
                    if (blocks[i][j]->isExplode())
                    {
                        blocks[i][j]->blockTexture.path = "page_game/" + theme + "mine.png";
                    }
                    else
                    {
                        blocks[i][j]->blockTexture.path = "page_game/" + theme + "mine_unrevealed.png";
                    }
                    drawCachedTexture(window, blocks[i][j]->blockTexture, gameBoardTexture);
                }
                else if (blocks[i][j]->getType() == NUMBER || blocks[i][j]->getType() == EMPTY)
                {
                    blocks[i][j]->blockTexture.path = transformMineCountToTextureName(blocks[i][j]->getMineCountAround());
                    drawCachedTexture(window, blocks[i][j]->blockTexture, gameBoardTexture);
                }
            }
        }
    }
}


int CGameBoard::findMineCountAround(int x, int y)
{
    // Find the number of mines around this block.
    int mineCoutAround = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < boardSizeX && j >= 0 && j < boardSizeY && !(i == x && j == y))
            {
                if (blocks[i][j]->getType() == MINE)
                {
                    mineCoutAround++;
                }
            }
        }
    }
    return mineCoutAround;
}

// Set the mine count around for target blocks.
void CGameBoard::setMineCountAroundForBlock(int x, int y)
{
    // Set the mine count around for this block.
    if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY)
    {
        blocks[x][y]->setMineCountAround(findMineCountAround(x, y), x, y, boardSizeX, boardSizeY);
    }
}

// Reveal nearby safe blocks starting from (startX, startY). BFS algorithm.
void CGameBoard::revealAroundSafeBlock(int startX, int startY)
{
    cout << "\33[32m[DEBUG]\33[0m Reveal nearby safe block at (" << startX << ", " << startY << ")" << endl;
    // Check if starting position is valid
    if (startX < 0 || startX >= boardSizeX || startY < 0 || startY >= boardSizeY)
        return;

    // Create a queue using vector to store blocks to reveal
    std::vector<std::pair<int, int>> queue;
    queue.push_back({startX, startY});

    while (!queue.empty())
    {
        // Pop the front block
        auto [x, y] = queue.back();
        queue.pop_back();

        // Skip if out of bounds
        if (x < 0 || x >= boardSizeX || y < 0 || y >= boardSizeY)
            continue;

        CBlock *block = blocks[x][y].get();

        // Skip if already revealed or not safe
        if (block->isRevealed() || block->getType() != EMPTY && block->getType() != NUMBER) 
            continue;

        // Skip if flagged
        if (block->isFlagged())
            continue;
            
        // Get mine count around this block
        int mineCount = findMineCountAround(x, y);

        // Set the block's mine count around.
        block->setMineCountAround(mineCount, x, y, boardSizeX, boardSizeY);

        // Reveal the block
        revealBlock(x, y);

        // If there are mines around, skip this block
        if (mineCount > 0)
            continue;

        // If there are no mines around, add neighbors to queue
        if (mineCount == 0)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    if (dx == 0 && dy == 0)
                        continue;
                    int nx = x + dx;
                    int ny = y + dy;

                    // Check bounds and add to queue
                    if (nx >= 0 && nx < boardSizeX && ny >= 0 && ny < boardSizeY)
                    {
                        // If neighbor is not revealed and is empty or number, add to queue.
                        if (blocks[nx][ny]->isRevealed() == false && (blocks[nx][ny]->getType() == EMPTY || blocks[nx][ny]->getType() == NUMBER))
                        {
                            queue.push_back({nx, ny});
                        }
                        else { // If neighbor is revealed or not empty, skip.
                            // Do nothing.
                        }
                    }
                }
            }
        }
    }
}

// Reveal nearby blocks if nearby flagged blocks equal to the number of the clicked block.
void CGameBoard::revealNearbyUnflaggedBlock(int x, int y)
{
    // Reveal nearby blocks.
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < boardSizeX && j >= 0 && j < boardSizeY && !(i == x && j == y))
            {
                // If neighbor is not revealed and is empty or number, add to queue.
                if (blocks[i][j]->isRevealed() == false && blocks[i][j]->isFlagged() == false )
                {
                    if (blocks[i][j]->getType() == NUMBER || blocks[i][j]->getType() == MINE)
                    {
                        // If it is number or mine, just reveal it.
                        revealBlock(i, j);
                    }
                    else if (blocks[i][j]->getType() == EMPTY)
                    {
                        // If it is empty, reveal it and its surrounding safe blocks.
                        revealAroundSafeBlock(i, j);
                    }
                    else; // Do nothing.
                }
                else { // If neighbor is revealed or flagged, skip.
                    // Do nothing.
                }
            }
        }
    }
}

// Get flagged blocks count around
int CGameBoard::getFlaggedBlocksCountAround(int x, int y)
{
    // Check if the block is out of bounds.
    if (x < 0 || x >= boardSizeX || y < 0 || y >= boardSizeY)
        return 0;
    
    int flaggedBlocksCount = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < boardSizeX && j >= 0 && j < boardSizeY && !(i == x && j == y))
            {
                if (blocks[i][j]->isFlagged())
                {
                    flaggedBlocksCount++;
                }
            }
        }
    }
    return flaggedBlocksCount;
}

// Reveal nearby safe blocks if revealed a block with number of mines around.
void CGameBoard::revealBlocksNearbyIfNearbyFlagsEqualNum(int x, int y)
{
    // Check if the block is revealed and has number of mines around.
    if (isBlockRevealed(x, y) == false || getBlockType(x, y) != NUMBER)
        return;
    
    // If the number of mines around is equal to the number of flagged blocks around, reveal nearby safe blocks.
    if (findMineCountAround(x, y) == getFlaggedBlocksCountAround(x, y))
    {
        revealNearbyUnflaggedBlock(x, y);
    }
    
}


// Win7 MineSweeper Feature
// Replace mines around to map randomly if clicked block is a mine or number block.
void CGameBoard::replaceSurroundingMinesAroundToMapRandomly(int x, int y)
{
    // Check if the block is out of bounds.
    if (x < 0 || x >= boardSizeX || y < 0 || y >= boardSizeY)
        return;

    // More implementation to be added.
}


// Initialize the game board. Here, set each block's texture infomation for further use.
void CGameBoard::initialize(int boardSizeX, int boardSizeY, int mineCount)
{
    // Initialize the game board.
    // Initialize the revealed blocks count.
    revealedBlocksCount = 0;
    // Initialize the mine count.
    this->mineCount = mineCount;

    // Initialize the board size.
    this->boardSizeX = boardSizeX;
    this->boardSizeY = boardSizeY;

    // Generate the game board area according to the board size, align to the center of the virtual window.
    float blockSizeX = (WindowSizeX - 80) / boardSizeX;
    float blockSizeY = (WindowSizeY - 80) / boardSizeY;
    float blockSize = std::min(blockSizeX, blockSizeY);
    float boardX = blockSize * boardSizeX;
    float boardY = blockSize * boardSizeY;
    float boardStartX = (WindowSizeX - boardX) / 2;
    float boardStartY = (WindowSizeY - boardY) / 2;

    // Set the game board area.
    boardArea = sf::FloatRect(boardStartX, boardStartY, boardX, boardY);

    // Set the row size of the game board.
    // Attention: Avoid resizing blocks behind the first block of the column,
    // which will cause compile error, 'cause unique_ptr can't be copied.
    blocks.resize(boardSizeX);
    for (int i = 0; i < boardSizeX; ++i)
    {
        blocks[i].resize(boardSizeY);
    }

    // Now randomly initialize the blocks with mine blocks and safe blocks.
    // brife: Step1 - Create a list of all blocks positions and give each block a unique coordination.
    //        Step2 - Shuffle the list randomly.
    //        Step3 - Place mines in the shuffled list from begin (0) to preset mine counts - 1 (mineCount - 1).
    //        Step4 - Fill the remaining blocks with safe blocks.

    // Step 1: Generate all possible positions on the board.
    std::vector<std::pair<int, int>> allPositions;
    for (int i = 0; i < boardSizeX; ++i)
    {
        for (int j = 0; j < boardSizeY; ++j)
        {
            allPositions.emplace_back(i, j);
        }
    }

    // Step 2: Shuffle the positions randomly.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allPositions.begin(), allPositions.end(), gen);

    // Step 3: Place mines at the first mineCount positions.
    for (int k = 0; k < mineCount && k < allPositions.size(); ++k)
    {
        int i = allPositions[k].first;
        int j = allPositions[k].second;
        blocks[i][j] = std::make_unique<CMineBlock>();
        blocks[i][j]->setType(MINE);
    }

    // Step 4: Fill the remaining blocks with safe blocks.
    for (int k = mineCount; k < allPositions.size(); ++k)
    {
        int i = allPositions[k].first;
        int j = allPositions[k].second;
        blocks[i][j] = std::make_unique<CSafeBlock>();
    }

    // Step 5: Set the parameter of each block.
    for (int i = 0; i < boardSizeX; ++i)
    {
        for (int j = 0; j < boardSizeY; ++j)
        {
            // Get the position of the block. (Area)
            sf::FloatRect blockPosition = sf::FloatRect(boardStartX + i * blockSize, boardStartY + j * blockSize, blockSize, blockSize);
            // Set the position of the block.
            blocks[i][j]->blockTexture.size = {blockSize, blockSize};
            blocks[i][j]->setPosition(blockPosition);
        }
    }

    // Step 6: Set the mine count around each safe block and determine its type.
    for (int i = 0; i < boardSizeX; ++i)
    {
        for (int j = 0; j < boardSizeY; ++j)
        {
            // If the block is mine block, skip once.
            if (blocks[i][j]->getType() == MINE)
                continue;

            // Set the mine count around the block.
            int count = findMineCountAround(i, j);
            blocks[i][j]->setMineCountAround(count, i, j, boardSizeX, boardSizeY);
            blocks[i][j]->setType(count > 0 ? NUMBER : EMPTY);
            blocks[i][j]->blockTexture.path = transformMineCountToTextureName(count);
        }
    }
}

// Update gameboard's area and blocks' visual parameter when window resized.
void CGameBoard::updateBoardAndBlockVisualization()
{
    // Update gameboard's area.
    float blockSizeX = (WindowSizeX - 80) / boardSizeX;
    float blockSizeY = (WindowSizeY - 80) / boardSizeY;
    float blockSize = std::min(blockSizeX, blockSizeY);
    float boardX = blockSize * boardSizeX;
    float boardY = blockSize * boardSizeY;
    float boardStartX = (WindowSizeX - boardX) / 2;
    float boardStartY = (WindowSizeY - boardY) / 2;
    boardArea = sf::FloatRect(boardStartX, boardStartY, boardX, boardY);

    // Update blocks' position.
    for (int i = 0; i < boardSizeX; ++i)
    {
        for (int j = 0; j < boardSizeY; ++j)
        {
            // Get the position of the block. (Area)
            sf::FloatRect blockPosition = sf::FloatRect(boardStartX + i * blockSize, boardStartY + j * blockSize, blockSize, blockSize);
            // Set the position of the block.
            blocks[i][j]->setPosition(blockPosition);
            // Set the size of the block.
            blocks[i][j]->blockTexture.size = {blockSize, blockSize};
        }
    }
}

// Returns the grid position (column, row) of the block that was clicked by the mouse.
// Only responds to left mouse button clicks within the board boundaries.
sf::Vector2i CGameBoard::getClickedBlockPosition(sf::RenderWindow &window, const sf::Event &event, const sf::FloatRect &boardBounds, const float blockSize)
{
    // Check if the event is a left mouse button press
    if (event.type != sf::Event::MouseButtonPressed)
        return sf::Vector2i(-1, -1); // Invalid click, return sentinel value

    // Get the mouse position relative to the window
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

    // Convert pixel coordinates to world coordinates (accounts for view transformations)
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    // Check if the calculated position is within the board boundaries
    if (!boardBounds.contains(worldPos))
        return sf::Vector2i(-1, -1); // Click outside the board

    // Calculate the block indices based on block size
    int col = static_cast<int>(worldPos.x - boardBounds.left) / blockSize;
    int row = static_cast<int>(worldPos.y - boardBounds.top) / blockSize;

    // Debug Output
    // if (event.mouseButton.button == sf::Mouse::Left)
    //     cout << "\033[34m[INFO]\033[0m Left clicked block position: (" << col << ", " << row << ")" << endl;
    // else if (event.mouseButton.button == sf::Mouse::Right)
    //     cout << "\033[34m[INFO]\033[0m Right clicked block position: (" << col << ", " << row << ")" << endl;

    // Return the valid block position
    return sf::Vector2i(col, row);
}


// Transform the mine count to the texture name.
const std::string transformMineCountToTextureName(int mineCount)
{
    // According to global setting to decide which theme to use.
    std::string theme = transformThemeToTextureThemePath(globalSettings.theme);

    switch (mineCount)
    {
    case -1:
        return "page_game/" + theme + "mine.png";
    case 0:
        return "page_game/" + theme + "empty.png";
    case 1:
        return "page_game/" + theme + "num1.png";
    case 2:
        return "page_game/" + theme + "num2.png";
    case 3:
        return "page_game/" + theme + "num3.png";
    case 4:
        return "page_game/" + theme + "num4.png";
    case 5:
        return "page_game/" + theme + "num5.png";
    case 6:
        return "page_game/" + theme + "num6.png";
    case 7:
        return "page_game/" + theme + "num7.png";
    case 8:
        return "page_game/" + theme + "num8.png";
    default:
        return "page_game/" + theme + "empty.png";
    }
}

// Transform the theme to the texture theme path.

const std::string transformThemeToTextureThemePath(int theme)
{
    switch (theme)
    {
    case DARK:
        return "dark_theme/";
    case LIGHT:
        return "light_theme/";
    case CLASSICAL:
        return "classical/";
    default:
        return "light_theme/";
    }
}

void CGameBoard::preloadGameBoardTexture(const std::string &theme)
{
    if (globalSettings.theme != CLASSICAL) // Especially for classical theme, because classical theme has no hover texture.
        preloadTexture("page_game/" + theme + "block_hover.png", gameBoardTexture);
    
    preloadTexture("page_game/" + theme + "block.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "mine.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "mine_unrevealed.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "flag.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "empty.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "num1.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "num2.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "num3.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "num4.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "num5.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "num6.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "num7.png", gameBoardTexture);
    preloadTexture("page_game/" + theme + "num8.png", gameBoardTexture);
    isTextureLoaded = true;
}

void CGameBoard::freeGameBoardTexture()
{
    freePreloadTextureCache(gameBoardTexture);
    isTextureLoaded = false;
}