// This file contains the definition of the Block class.
#pragma once

#include "visualize.hpp"
#include <vector>
#include <memory>
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
    void setPosition(sf::FloatRect position) { this->position = position; };
    sf::FloatRect getPosition() const { return position; };

protected:
    bool revealed; // Whether this block has been revealed.
    short type; // The type of this block, which can be SAFE, MINE or UNKNOWN.

    sf::FloatRect position; // The position of this block in the game board.
// define friend function to access private member
};


class CSafeBlock : public CBlock {
    // Represents a safe block, which is empty or has a number of mines around it, showing mines count around.
public:
    CSafeBlock() : CBlock() { type = SAFE; };
    void findMineCountAround(vector<vector<CBlock *>> &normboard, int x, int y, int rows, int cols);

private:
    short mineCoutAround; // The number of mines around this block.
};


class CMineBlock : public CBlock {
    // Represents a mine block.
public:
    CMineBlock() : CBlock() { type = MINE; };
    void explode() { /* Code to handle explosion */ };
};

// Gameboard class
class CGameBoard
{
public:
    // Initialize the game board.
    void initialize(int boardSizeX = 10, int boardSizeY = 10);

    // Update the game board.
    void update();

    // Render the game board.
    void render(sf::RenderWindow &window);

private:
    // Game board size. (Default 10x10)
    int boardSizeX;
    int boardSizeY;

    // Game board blocks. (Unknown size, waiting for initialization)
    // Here, use unique_ptr to manage the memory of the blocks.
    std::vector<std::vector<std::unique_ptr<CBlock>>> blocks;
    // Game board area.
    sf::FloatRect boardArea;
};