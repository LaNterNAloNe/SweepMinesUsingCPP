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
    CGlobalGameSetting() : theme(LIGHT) {}

    short theme;
};

// Set extern global game settings. main.cpp define a instance, so that each cpp can apply to it.
extern CGlobalGameSetting globalSettings;