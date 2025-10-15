// PageGame.hpp
/*
    The game page.
*/

#pragma once

#include "Page.hpp"
#include "visualize.hpp"
#include "blocks.hpp"
#include "debug.hpp"



class CPageGame : public CPage
{
public:
    CPageGame() : 
        returnButton("page_game/return.png", updateReturnButtonPosition(), updateReturnButtonSize()),
        restartButton("page_game/restart.png", updateRestartButtonPosition(), updateRestartButtonSize()),
        notificationToPlayer("Select difficulty or customize map", 40, sf::Color::Black, CENTER, updateNotificationToPlayerPosition()),
        difficultyEasy("Easy", 40, sf::Color::Black, CENTER, updateDifficultyEasyPosition()),
        difficultyMedium("Medium", 40, sf::Color::Black, CENTER, updateDifficultyMediumPosition()),
        difficultyHard("Hard", 40, sf::Color::Black, CENTER, updateDifficultyHardPosition())
        {}
    // See the comments in Page.hpp for the function's functionality.
    void handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages) override;
    void update(sf::RenderWindow &window, sf::Event event) override;
    void render(sf::RenderWindow &window, sf::Event event) override;
    bool getIsInGame() { return isInGame; }
    bool getIsInitialized() { return isInitialized; }
    // // Game start state.
    // void setGameStart(bool gameStart) { isGameStart = gameStart; }

    // Check if game finished.
    bool checkIsTextureLoaded() { return isTextureLoaded; };

    ~CPageGame() override {}
private:
    // Back to beginning page.
    void backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages);
    void restartGame();

    // Start game.
    enum DIFFICULTY {
        NONE = 0,
        DIFFICULTY_EASY,
        DIFFICULTY_MEDIUM,
        DIFFICULTY_HARD
    };
    void startGame(int difficulty);

    // Load and free texture cache
    void preloadFunctionButtonTexture();
    void freeFunctionButtonTexture();

    // Game board.
    CGameBoard gameBoard;

    // Game parameter
    // Game start state.
    bool isMapDefined = false;
    int difficultyChosen = NONE;
    bool isInitialized = false;
    bool isInGame = false;
    bool isGameOver = false;

    // Texture cache.
    TextureCache functionButtonTexture;
    bool isTextureLoaded = false;

    // Function buttons: return.
    CVisualTexture returnButton;
    sf::Vector2f updateReturnButtonPosition() { return sf::Vector2f(WindowSizeX * 0.03f, WindowSizeX * 0.03f); }
    sf::Vector2f updateReturnButtonSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeX / 1920.f * 50.f); }

    // Function buttons: restart.
    CVisualTexture restartButton;
    sf::Vector2f updateRestartButtonPosition() { return sf::Vector2f(WindowSizeX - WindowSizeX * 0.03f, WindowSizeX * 0.03f); }
    sf::Vector2f updateRestartButtonSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeX / 1920.f * 50.f); }

    // Notification text that tell user to choose difficulty.
    CVisualText notificationToPlayer;
    sf::Vector2f updateNotificationToPlayerPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.3f); }

    // Difficulty buttons: easy.
    CVisualText difficultyEasy;
    sf::Vector2f updateDifficultyEasyPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.5f); }

    // Difficulty buttons: medium.
    CVisualText difficultyMedium;
    sf::Vector2f updateDifficultyMediumPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.6f); }

    // Difficulty buttons: hard.
    CVisualText difficultyHard;
    sf::Vector2f updateDifficultyHardPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.7f); }
};
