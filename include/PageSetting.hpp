// PageSetting.hpp

/*
This header file contains the global settings of the game.
*/

#pragma once

// Visual theme.
enum _theme
{
    LIGHT = 0,
    DARK,
    CLASSICAL,
};

// Global game settings definition.
class CGlobalGameSetting
{
public:
    // Default constructor.
    CGlobalGameSetting() // Representing default settings.
    {
        // Visual settings
        theme = LIGHT;
        fullScreen = false;
        showFPS = false;
        showMouseTrail = true;

        // Game settings
        useWin7MineSweeperFeature = true;
    }

    // Visual settings
    short theme; // Visual theme.
    bool fullScreen; // Whether to use full screen.
    bool showFPS; // Whether to show FPS.
    bool showMouseTrail; // Whether to show mouse trail.

    // Game settings
    bool useWin7MineSweeperFeature; // Use Win7 MineSweeper feature: Fast reveal.
};

// Set extern global game settings. main.cpp define a instance, so that each cpp can apply to it.
extern CGlobalGameSetting globalSettings;