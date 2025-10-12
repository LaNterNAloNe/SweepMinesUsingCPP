// PageGame.hpp
/*
    The game page.
*/

#pragma once

#include "Page.hpp"
#include "visualize.hpp"
#include "blocks.hpp"


class CPageGame : public CPage
{
public:
    // See the comments in Page.hpp for the function's functionality.
    void handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages) override;
    void update(sf::RenderWindow &window) override;
    void render(sf::RenderWindow &window) override;
    bool getIsInGame() { return isInGame; }
    bool getIsInitialized() { return isInitialized; }
    // Game start state.
    void setGameStart(bool gameStart) { isGameStart = gameStart; }
    ~CPageGame() override {}
private:
    // Back to beginning page.
    void backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages);

    // Game board.
    CGameBoard gameBoard;

    // Game parameter
    // Game start state.
    bool isGameStart = true;
    bool isInitialized = false;
    bool isInGame = false;
};


