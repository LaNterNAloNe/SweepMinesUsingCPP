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
        backToChooseDifficultyButton("page_game/backtochoose.png", updateBackToChooseDifficultyButtonPosition(), updateBackToChooseDifficultyButtonSize()),
        notificationToPlayer("Select difficulty or customize map", 40, sf::Color::Black, CENTER, updateNotificationToPlayerPosition()),
        difficultyEasy("Easy", 40, sf::Color::Black, CENTER, updateDifficultyEasyPosition()),
        difficultyMedium("Medium", 40, sf::Color::Black, CENTER, updateDifficultyMediumPosition()),
        difficultyHard("Hard", 40, sf::Color::Black, CENTER, updateDifficultyHardPosition()),
        customMap("Customize", 40, sf::Color::Black, CENTER, updateCustomMapPosition()),
        customMapInputBox_X(updateCustomMapInputBox_XPosition(), updateCustomMapInputBox_XSize(), "font.ttf", 40, "X", 2),
        customMapInputBox_Y(updateCustomMapInputBox_YPosition(), updateCustomMapInputBox_YSize(), "font.ttf", 40, "Y", 2),
        customMapInputBox_Mine(updateCustomMapInputBox_MinePosition(), updateCustomMapInputBox_MineSize(), "font.ttf", 40, "Mine", 3),
        comfirmCustomMap("Confirm", 40, sf::Color::Black, CENTER, updateComfirmCustomMapPosition()),
        backToDifficulty("Back to difficulty", 40, sf::Color::Black, CENTER, updateBackToDifficultyPosition())
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
        DIFFICULTY_HARD,
        DIFFICULTY_CUSTOM,
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
    bool isCustomizingMap = false;
    int difficultyChosen = NONE;
    bool isInitialized = false;
    bool isInGame = false;
    bool isGameOver = false;

    // Texture cache.
    TextureCache functionButtonTexture;
    bool isTextureLoaded = false;

    // For custiomize map playing.
    int CustomSizeX;
    int CustomSizeY;
    int CustomMines;

    // Here are visual elements below:

    // Function buttons: return.
    CVisualTexture returnButton;
    sf::Vector2f updateReturnButtonPosition() { return sf::Vector2f(WindowSizeX * 0.03f, WindowSizeX * 0.03f); }
    sf::Vector2f updateReturnButtonSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeX / 1920.f * 50.f); }

    // Function buttons: restart.
    CVisualTexture restartButton;
    sf::Vector2f updateRestartButtonPosition() { return sf::Vector2f(WindowSizeX - WindowSizeX * 0.03f, WindowSizeX * 0.03f); }
    sf::Vector2f updateRestartButtonSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeX / 1920.f * 50.f); }

    // Function buttons: back to choose difficulty.
    CVisualTexture backToChooseDifficultyButton;
    sf::Vector2f updateBackToChooseDifficultyButtonPosition() { return sf::Vector2f(WindowSizeX - WindowSizeX * 0.03f, WindowSizeY * 0.13f); }
    sf::Vector2f updateBackToChooseDifficultyButtonSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeX / 1920.f * 50.f); }

    // Notification text that tell user to choose difficulty.
    CVisualText notificationToPlayer;
    sf::Vector2f updateNotificationToPlayerPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.3f); }

    // Difficulty buttons: easy.
    CVisualText difficultyEasy;
    sf::Vector2f updateDifficultyEasyPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.4f); }

    // Difficulty buttons: medium.
    CVisualText difficultyMedium;
    sf::Vector2f updateDifficultyMediumPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.5f); }

    // Difficulty buttons: hard.
    CVisualText difficultyHard;
    sf::Vector2f updateDifficultyHardPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.6f); }

    // Customize map button.
    CVisualText customMap;
    sf::Vector2f updateCustomMapPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.7f); }

    // Customize map input box (X).
    CInputBox customMapInputBox_X;
    sf::Vector2f updateCustomMapInputBox_XPosition() { return sf::Vector2f(WindowSizeX * 0.4f, WindowSizeY * 0.45f); }
    sf::Vector2f updateCustomMapInputBox_XSize() { return sf::Vector2f(WindowSizeX / 1920.f * 200.f, WindowSizeX / 1920.f * 100.f); }
    sf::Vector2f updateCustomMapInputBox_XFontSize() { return sf::Vector2f(WindowSizeX / 1920.f * 40.f, WindowSizeX / 1920.f * 40.f); }

    // Customize map input box (Y).
    CInputBox customMapInputBox_Y;
    sf::Vector2f updateCustomMapInputBox_YPosition() { return sf::Vector2f(WindowSizeX * 0.6f, WindowSizeY * 0.45f); }
    sf::Vector2f updateCustomMapInputBox_YSize() { return sf::Vector2f(WindowSizeX / 1920.f * 200.f, WindowSizeX / 1920.f * 100.f); }
    sf::Vector2f updateCustomMapInputBox_YFontSize() { return sf::Vector2f(WindowSizeX / 1920.f * 40.f, WindowSizeX / 1920.f * 40.f); }

    // Customize map input box (Mine).
    CInputBox customMapInputBox_Mine;
    sf::Vector2f updateCustomMapInputBox_MinePosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.55f); }
    sf::Vector2f updateCustomMapInputBox_MineSize() { return sf::Vector2f(WindowSizeX / 1920.f * 200.f, WindowSizeX / 1920.f * 100.f); }
    sf::Vector2f updateCustomMapInputBox_MineFontSize() { return sf::Vector2f(WindowSizeX / 1920.f * 40.f, WindowSizeX / 1920.f * 40.f); }

    // Customize map confirm button.
    CVisualText comfirmCustomMap;
    sf::Vector2f updateComfirmCustomMapPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.7f); }

    // Back to difficulty button.
    CVisualText backToDifficulty;
    sf::Vector2f updateBackToDifficultyPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.8f); }
};
