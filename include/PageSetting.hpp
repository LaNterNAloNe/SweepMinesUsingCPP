// PageSetting.hpp

/*
This header file contains the global settings of the game.
*/

#pragma once

#include "Page.hpp"
#include "visualize.hpp"
#include "debug.hpp"

// Visual theme.
enum _theme
{
    LIGHT = 0,
    DARK,
    CLASSICAL,
};

// Global game settings definition.
class CPageSettings : public CPage
{
public:
    // Default constructor.
    CPageSettings() : 
        returnButton("page_settings/return.png", updateReturnButtonPosition(), updateReturnButtonSize()),
        themeText("Theme", 50, sf::Color::Black, RIGHT, updateThemeTextPosition()),
        themeOptionLightText("Light", 30, sf::Color::Black, CENTER, updateThemeOptionLightTextPosition()),
        themeOptionDarkText("Dark", 30, sf::Color::Black, CENTER, updateThemeOptionDarkTextPosition()),
        themeOptionClassicalText("Classical", 30, sf::Color::Black, CENTER, updateThemeOptionClassicalTextPosition()),
        // Not to set content here, set in relative cpp file dynamically.
        themeOptionLightTexture("", updateThemeOptionLightTexturePosition(), updateThemeOptionLightTextureSize()),
        themeOptionDarkTexture("", updateThemeOptionDarkTexturePosition(), updateThemeOptionDarkTextureSize()),
        themeOptionClassicalTexture("", updateThemeOptionClassicalTexturePosition(), updateThemeOptionClassicalTextureSize()),
        fullscreenOptionText("Fullscreen", 50, sf::Color::Black, RIGHT, updateFullscreenOptionTextPosition()),
        fullscreenOptionTexture("", updateFullscreenOptionTexturePosition(), updateFullscreenOptionTextureSize()),
        showFPSOptionText("Show FPS", 50, sf::Color::Black, RIGHT, updateShowFPSOptionTextPosition()),
        showFPSOptionTexture("", updateShowFPSOptionTexturePosition(), updateShowFPSOptionTextureSize()),
        showMouseTrailOptionText("Show Mouse Trail", 50, sf::Color::Black, RIGHT, updateShowMouseTrailOptionTextPosition()),
        showMouseTrailOptionTexture("", updateShowMouseTrailOptionTexturePosition(), updateShowMouseTrailOptionTextureSize()),
        win7FeatureOptionText("Win7 Feature", 50, sf::Color::Black, RIGHT, updateWin7FeatureOptionTextPosition()),
        win7FeatureOptionTexture("", updateWin7FeatureOptionTexturePosition(), updateWin7FeatureOptionTextureSize())
    {}

    void handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages);
    void update(sf::RenderWindow &window, sf::Event event);
    void render(sf::RenderWindow &window, sf::Event event);

    /* Here are texture preload and free */

    // Preload and free settings page texture cache.
    TextureCache settingsPageTexture;

    void preloadSettingsPageTexture();
    void freeSettingsPageTexture();

    bool isTextureLoaded = false;

    // Handle back to beginning page.
    void backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages);


    /* Here are visual elements bellow: */

    // Function button: Return.
    CVisualTexture returnButton;
    sf::Vector2f updateReturnButtonPosition() { return sf::Vector2f(WindowSizeX * 0.03f, WindowSizeX * 0.03f); }
    sf::Vector2f updateReturnButtonSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeX / 1920.f * 50.f); }

    // Setting option 1: Theme.
    CVisualText themeText;
    sf::Vector2f updateThemeTextPosition() { return sf::Vector2f(WindowSizeX * 0.4f, WindowSizeY * 0.2f); }
    sf::Vector2f updateThemeTextSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }

    CVisualText themeOptionLightText;
    sf::Vector2f updateThemeOptionLightTextPosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.23f); }
    sf::Vector2f updateThemeOptionLightTextSize() { return sf::Vector2f(WindowSizeX / 1920.f * 30.f, WindowSizeY / 1080.f * 30.f); }

    CVisualTexture themeOptionLightTexture;
    sf::Vector2f updateThemeOptionLightTexturePosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.17f); }
    sf::Vector2f updateThemeOptionLightTextureSize() { return sf::Vector2f(WindowSizeX / 1920.f * 30.f, WindowSizeY / 1080.f * 30.f); }

    CVisualText themeOptionDarkText;
    sf::Vector2f updateThemeOptionDarkTextPosition() { return sf::Vector2f(WindowSizeX * 0.6f, WindowSizeY * 0.23f); }
    sf::Vector2f updateThemeOptionDarkTextSize() { return sf::Vector2f(WindowSizeX / 1920.f * 30.f, WindowSizeY / 1080.f * 30.f); }

    CVisualTexture themeOptionDarkTexture;
    sf::Vector2f updateThemeOptionDarkTexturePosition() { return sf::Vector2f(WindowSizeX * 0.6f, WindowSizeY * 0.17f); }
    sf::Vector2f updateThemeOptionDarkTextureSize() { return sf::Vector2f(WindowSizeX / 1920.f * 30.f, WindowSizeY / 1080.f * 30.f); }

    CVisualText themeOptionClassicalText;
    sf::Vector2f updateThemeOptionClassicalTextPosition() { return sf::Vector2f(WindowSizeX * 0.7f, WindowSizeY * 0.23f); }
    sf::Vector2f updateThemeOptionClassicalTextSize() { return sf::Vector2f(WindowSizeX / 1920.f * 30.f, WindowSizeY / 1080.f * 30.f); }

    CVisualTexture themeOptionClassicalTexture;
    sf::Vector2f updateThemeOptionClassicalTexturePosition() { return sf::Vector2f(WindowSizeX * 0.7f, WindowSizeY * 0.17f); }
    sf::Vector2f updateThemeOptionClassicalTextureSize() { return sf::Vector2f(WindowSizeX / 1920.f * 30.f, WindowSizeY / 1080.f * 30.f); }

    CVisualText fullscreenOptionText;
    sf::Vector2f updateFullscreenOptionTextPosition() { return sf::Vector2f(WindowSizeX * 0.4f, WindowSizeY * 0.3f); }
    sf::Vector2f updateFullscreenOptionTextSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }

    CVisualTexture fullscreenOptionTexture;
    sf::Vector2f updateFullscreenOptionTexturePosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.3f); }
    sf::Vector2f updateFullscreenOptionTextureSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }

    CVisualText showFPSOptionText;
    sf::Vector2f updateShowFPSOptionTextPosition() { return sf::Vector2f(WindowSizeX * 0.4f, WindowSizeY * 0.4f); }
    sf::Vector2f updateShowFPSOptionTextSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }

    CVisualTexture showFPSOptionTexture;
    sf::Vector2f updateShowFPSOptionTexturePosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.4f); }
    sf::Vector2f updateShowFPSOptionTextureSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }

    CVisualText showMouseTrailOptionText;
    sf::Vector2f updateShowMouseTrailOptionTextPosition() { return sf::Vector2f(WindowSizeX * 0.4f, WindowSizeY * 0.5f); }
    sf::Vector2f updateShowMouseTrailOptionTextSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }

    CVisualTexture showMouseTrailOptionTexture;
    sf::Vector2f updateShowMouseTrailOptionTexturePosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.5f); }
    sf::Vector2f updateShowMouseTrailOptionTextureSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }

    CVisualText win7FeatureOptionText;
    sf::Vector2f updateWin7FeatureOptionTextPosition() { return sf::Vector2f(WindowSizeX * 0.4f, WindowSizeY * 0.6f); }
    sf::Vector2f updateWin7FeatureOptionTextSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }

    CVisualTexture win7FeatureOptionTexture;
    sf::Vector2f updateWin7FeatureOptionTexturePosition() { return sf::Vector2f(WindowSizeX * 0.5f, WindowSizeY * 0.6f); }
    sf::Vector2f updateWin7FeatureOptionTextureSize() { return sf::Vector2f(WindowSizeX / 1920.f * 50.f, WindowSizeY / 1080.f * 50.f); }
};

struct GameSettings
{
    // Visual settings
    short theme; // Visual theme.
    bool fullScreen; // Whether to use full screen.
    bool showFPS; // Whether to show FPS.
    bool showMouseTrail; // Whether to show mouse trail.

    // Game settings
    bool useWin7MineSweeperFeature; // Use Win7 MineSweeper feature: First click never be a mine.
};

extern GameSettings globalSettings;