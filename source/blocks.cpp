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