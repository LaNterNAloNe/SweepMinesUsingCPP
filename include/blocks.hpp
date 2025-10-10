// This file contains the definition of the Block class.
#pragma once

#include <vector>
using std::vector;

#define SAFE 0
#define MINE -1
#define UNKNOWN -2

/* classical block class are as follows */
class CBlock { 
    // Represents a abstract block class, which is the base class of CSafeBlock and CMineBlock, even any other types of blocks.
public:
    CBlock() : revealed(false), type(UNKNOWN){};
    void reveal() { revealed = true; };
    bool isRevealed() const { return revealed; };
    short getType() const { return type; }

protected:
    bool revealed; // Whether this block has been revealed.
    short type; // The type of this block, which can be SAFE, MINE or UNKNOWN.
};


class CSafeBlock : public CBlock {
    // Represents a safe block, which is empty or has a number of mines around it, showing mines count around.
public:
    CSafeBlock() : CBlock() { type = SAFE; };
    void findMineCountAround(vector<vector<CBlock *>> &normboard, int x, int y, int rows, int cols);

private:
    short mineCoutAround; // The number of mines around this block.
};

void CSafeBlock::findMineCountAround(vector<vector<CBlock*>> &normboard, int x, int y, int rows, int cols) {
    // Find the number of mines around this block.
    mineCoutAround = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < cols && !(i == x && j == y)) {
                if (normboard[i][j]->getType() == MINE) {
                    mineCoutAround++;
                }
            }
        }
    }
}


class CMineBlock : public CBlock {
    // Represents a mine block.
public:
    CMineBlock() : CBlock() { type = MINE; };
    void explode() { /* Code to handle explosion */ };
};
