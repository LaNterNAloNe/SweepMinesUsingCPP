#include "../include/blocks.hpp"

// Block class implementation


/* SafeBlock class implementation */
void CSafeBlock::findMineCountAround(vector<vector<CBlock *>> &normboard, int x, int y, int rows, int cols)
{
    // Find the number of mines around this block.
    mineCoutAround = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < rows && j >= 0 && j < cols && !(i == x && j == y))
            {
                if (normboard[i][j]->getType() == MINE)
                {
                    mineCoutAround++;
                }
            }
        }
    }
}

// Gameboard Function
void CGameBoard::initialize(int boardSizeX, int boardSizeY)
{
    // Initialize the game board.
    // change size
    this->boardSizeX = boardSizeX;
    this->boardSizeY = boardSizeY;

    // Generate the game board area according to the board size, align to the center of the virtual window.
    float blockSize = (VIRTUAL_WINDOW_SIZE_Y - 80) / boardSizeY;
    float boardX = blockSize * boardSizeX;
    float boardY = blockSize * boardSizeY;
    float boardStartX = (VIRTUAL_WINDOW_SIZE_X - boardX) / 2;
    float boardStartY = (VIRTUAL_WINDOW_SIZE_Y - boardY) / 2;

    // Set the game board area.
    boardArea = sf::FloatRect(boardStartX, boardStartY, boardX, boardY);

    // Set the row size of the game board.
    // Attention: Avoid resizing blocks behind the first block of the column,
    // which will cause compile error, 'cause unique_ptr can't be copied.
    blocks.resize(boardSizeX);

    for (int i = 0; i < boardSizeX; ++i)
    {
        // Set the column size of the game board.
        blocks[i].resize(boardSizeY);

        for (int j = 0; j < boardSizeY; ++j)
        {
            // now just test the mine blocks' generation
            bool isMine = (rand() % 10 == 0);
            if (isMine)
                blocks[i][j] = std::make_unique<CMineBlock>();
            else
                blocks[i][j] = std::make_unique<CSafeBlock>();

            // Get the position of the block. (Area)
            sf::FloatRect blockPosition = sf::FloatRect(boardStartX + (i + 0.5) * blockSize, boardStartY + (j + 0.5) * blockSize, blockSize, blockSize);
        }
    }
}

void CGameBoard::update()
{
    // Update the game board.
}

void CGameBoard::render(sf::RenderWindow &window)
{
    // Render the game board, using cached texture. (Must)
    for (int i = 0; i < boardSizeX; ++i)
    {
        for (int j = 0; j < boardSizeY; ++j)
        {
            if (blocks[i][j]->isRevealed() == false)
            {
                sf::FloatRect blockPosition = blocks[i][j]->getPosition();
                drawCachedTexture(window, blockPosition.left, blockPosition.top, blockPosition.width, "page_game/mine.png");
            }
        }
    }
}