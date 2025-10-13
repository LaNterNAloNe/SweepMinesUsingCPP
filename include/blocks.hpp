// This file contains the definition of the Block class.
#pragma once

#include "visualize.hpp"
#include "PageSetting.hpp"
#include <vector>
#include <memory>
#include <random>
using std::vector;

#define FLAG 3
#define NUMBER 2
#define EMPTY 1
#define SAFE 0 // Represents a safe block, which is empty or has a number of mines around it, showing mines count around. Attention: SAFE type should not be used unless neccessary
#define MINE -1
#define UNKNOWN -2

/* classical block class are as follows */
class CBlock { 
    // Represents a abstract block class, which is the base class of CSafeBlock and CMineBlock, even any other types of blocks.
public:
    CBlock() : revealed(false), type(UNKNOWN){};

    // Reveal this block.
    void reveal() { revealed = true; };
    bool isRevealed() const { return revealed; };

    // Set and get the type of this block.
    virtual void setType(short type) { this->type = type; }
    virtual short getType() const { return type; }

    // Set and get the flagged state of this block.
    void setFlagged(bool flagged) { this->flagged = flagged; }
    bool isFlagged() const { return flagged; }

    // Set and get the position of this block.
    void setPosition(sf::FloatRect position) { this->position = position; };
    sf::FloatRect getPosition() const { return position; };

    // now define virtual function for different derive class to override
    virtual void setMineCountAround (int count, int x, int y, int boardSizeX, int boardSizeY) { return; }
    virtual int getMineCountAround() const { return -1; }

    // Explode this block.
    virtual void explode() { return; }
    virtual bool isExplode() const { return exploded; }

protected:
    bool revealed; // Whether this block has been revealed. For each block.
    short type; // The type of this block, which can be SAFE, MINE or UNKNOWN. For each block.
    bool flagged = false; // Whether this block has been flagged. Defalt false. For each block.
    bool exploded = false; // Whether this block has been exploded. Defalt false. Especially for mine block.

    sf::FloatRect position; // The position of this block in the game board.
// define friend function to access private member
};

// Derive class: SafeBlock class
class CSafeBlock : public CBlock {
    // Represents a safe block, which is empty or has a number of mines around it, showing mines count around.
public:
    CSafeBlock() : CBlock() { mineCoutAround = 0; };
    short getType() const override { return type; }
    void setMineCountAround(int count, int x, int y, int boardSizeX, int boardSizeY) override;
    int getMineCountAround() const override {return mineCoutAround; }

private:
    short mineCoutAround; // The number of mines around this block.
};


// Derive class: MineBlock class
class CMineBlock : public CBlock {
    // Represents a mine block.
public:
    CMineBlock() : CBlock() { type = MINE; };
    short getType() const override { return type; }
    void setMineCountAround(int count, int x, int y, int boardSizeX, int boardSizeY) override { return; }
    int getMineCountAround() const override { return -1; }
    void explode() override { exploded = true; }
};


// Gameboard class
class CGameBoard
{
public:
    // Initialize the game board.
    void initialize(int boardSizeX = 30, int boardSizeY = 20, int mineCount = 80);

    // Handle game event
    void handleEvent(sf::RenderWindow &window, sf::Event &event);

    // Update the game board.
    void update();

    // Render the game board.
    void render(sf::RenderWindow &window, sf::Event &event);

    // get board area
    sf::FloatRect getBoardArea() const { return boardArea; }

    // get block's size in board
    float getBlockSize() const { return blocks[0][0]->getPosition().width; }

    // get board size
    int getBoardSizeX() const { return boardSizeX; }
    int getBoardSizeY() const { return boardSizeY; }

    // check if block is flagged
    bool isBlockFlagged(int x, int y) 
    { 
        if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) 
            return blocks[x][y]->isFlagged(); 
        else 
            return false; 
    }
    
    // set flagged state for block
    void setBlockFlagged(int x, int y, bool flagged) 
    { 
        if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) 
            blocks[x][y]->setFlagged(flagged); 
    }

    // Get flagged blocks count around
    int getFlaggedBlocksCountAround(int x, int y);

    // check if block is revealed
    bool isBlockRevealed(int x, int y) 
    { 
        if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) 
            return blocks[x][y]->isRevealed(); 
        else 
            return true; 
    }

    // reveal block
    void revealBlock(int x, int y) 
    { 
        if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) blocks[x][y]->reveal(), revealedBlocksCount++; 
        if (blocks[x][y]->getType() == MINE) blocks[x][y]->explode(), revealedMinesCount++, gameStatus = MINE_REVEALED; 
    }

    // Reveal nearby safe blocks if revealed a block with number of mines around equal to flagged blocks around.
    void revealBlocksNearbyIfNearbyFlagsEqualNum(int x, int y);

    // Get revealed block counts
    int getRevealedBlocksCount() const { return revealedBlocksCount; }
    
    // get block type
    short getBlockType(int x, int y) 
    { 
        if (x >= 0 && x < boardSizeX && y >= 0 && y < boardSizeY) return blocks[x][y]->getType(); 
        else return UNKNOWN; 
    }

    // find mine count around
    int findMineCountAround(int x, int y);

    // get mine count around
    void setMineCountAroundForBlock(int x, int y);

    // reveal all mines
    void revealAllMineBlocks() 
    { 
        for (int i = 0; i < boardSizeX; i++) 
            for (int j = 0; j < boardSizeY; j++) 
                if (blocks[i][j]->getType() == MINE) blocks[i][j]->reveal(); 
    }

    // Reveal surrounding safe blocks if revealed a empty block
    void revealAroundSafeBlock(int x, int y); // Represent revealing surrrounding safe blocks if revealed a empty block.
    void revealNearbyUnflaggedBlock(int x, int y); // Represent revealing nearby unflagged blocks if flagged blocks equal to mine blocks around 8 blocks.

    // Check if game finished
    bool isGameFinished() { return isGamewon || isGameLost != NONE; }
    bool isMineRevealed() { return isGameLost == MINE_REVEALED; }

    // Texture cache
    void preloadGameBoardTexture(std::string theme = "light_theme");
    void freeGameBoardTexture();
    bool checkIfTextureLoaded() { return isTextureLoaded; };

    // Reset the game board.
    void reset() 
    { 
        isGamewon = false; 
        isGameLost = false;
        gameStatus = NONE;
        revealedBlocksCount = 0;
        revealedMinesCount = 0;
        mineCount = 0;
        blocks.clear();
    }

    // Get clicked block position.
    sf::Vector2i getClickedBlockPosition(sf::RenderWindow &window, const sf::Event &event, const sf::FloatRect &boardBounds, const float blockSize);

private:
    // Game board size. (Default 10x10)
    int boardSizeX;
    int boardSizeY;

    // Game board blocks. (Unknown size, waiting for initialization)
    // Here, use unique_ptr to manage the memory of the blocks.
    std::vector<std::vector<std::unique_ptr<CBlock>>> blocks;
    // Game board area.
    sf::FloatRect boardArea;

    // Count revealed blocks
    int revealedBlocksCount;
    int revealedMinesCount;
    int mineCount;
    bool isGamewon = false;
    bool isGameLost = false;
    enum _gameStatus
    {
        NONE = 0, // Nothing special happenned.
        MINE_REVEALED = 1,
        WON = 2,
        LOST = 3,
        // Any other kind of condition awaiting for develop.
    } gameStatus;

    // Texture cache
    TextureCache gameBoardTexture;
    bool isTextureLoaded = false;
};

// Transform the mine count to the texture name.
const std::string transformMineCountToTextureName(int mineCount);
