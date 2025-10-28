#include "../include/PageSetting.hpp"

void CPageSettings::handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    // Handle events here.
    if (event.type == sf::Event::MouseButtonPressed)
    {
        // Check if return button is clicked.
        if (isMouseClickInArea(window, event, returnButton.area))
        {
            // Return to main menu.
            CPageSettings::backToBeginning(window, currentPage, pages);
            cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Return' button clicked." << endl;
        }
        else if (isMouseClickInArea(window, event, themeOptionLightTexture.area))
        {
            // Change theme to light.
            globalSettings.theme = LIGHT;
            cout << "\33[34m[INFO]\33[0m Theme changed to LIGHT." << endl;
        }
        else if (isMouseClickInArea(window, event, themeOptionDarkTexture.area))
        {
            // Change theme to dark.
            globalSettings.theme = DARK;
            cout << "\33[34m[INFO]\33[0m Theme changed to DARK." << endl;
        }
        else if (isMouseClickInArea(window, event, themeOptionClassicalTexture.area))
        {
            // Change theme to classical.
            globalSettings.theme = CLASSICAL;
            cout << "\33[34m[INFO]\33[0m Theme changed to CLASSICAL." << endl;
        }
        else if (isMouseClickInArea(window, event, fullscreenOptionTexture.area))
        {
            // Toggle fullscreen mode.
            globalSettings.fullScreen = !globalSettings.fullScreen;
            cout << "\33[34m[INFO]\33[0m Fullscreen mode " << (globalSettings.fullScreen ? "enabled" : "disabled") << "." << endl;
        }
        else if (isMouseClickInArea(window, event, showFPSOptionTexture.area))
        {
            // Toggle show FPS option.
            globalSettings.showFPS = !globalSettings.showFPS;
            cout << "\33[34m[INFO]\33[0m Show FPS option " << (globalSettings.showFPS ? "enabled" : "disabled") << "." << endl;
        }
        else if (isMouseClickInArea(window, event, showMouseTrailOptionTexture.area))
        {
            // Toggle show mouse trail option.
            globalSettings.showMouseTrail = !globalSettings.showMouseTrail;
            cout << "\33[34m[INFO]\33[0m Show mouse trail option " << (globalSettings.showMouseTrail ? "enabled" : "disabled") << "." << endl;
        }
        else if (isMouseClickInArea(window, event, win7FeatureOptionTexture.area))
        {
            // Toggle Win7 MineSweeper feature option.
            globalSettings.useWin7MineSweeperFeature = !globalSettings.useWin7MineSweeperFeature;
            cout << "\33[34m[INFO]\33[0m Win7 MineSweeper feature " << (globalSettings.useWin7MineSweeperFeature ? "enabled" : "disabled") << "." << endl;
        }
    }
}

void CPageSettings::update(sf::RenderWindow &window, sf::Event event)
{
    // Update visual elements positions and sizes when window resized.
    if (event.type == sf::Event::Resized || lastWindowSize != static_cast<sf::Vector2f>(window.getSize()))
    {
        // Update the lastWindowSize parameter in this page class.
        lastWindowSize = static_cast<sf::Vector2f>(window.getSize());

        returnButton.updateWhenWindowResize(updateReturnButtonPosition(), updateReturnButtonSize());

        themeText.updateWhenWindowResize(updateThemeTextPosition());
        themeOptionLightText.updateWhenWindowResize(updateThemeOptionLightTextPosition());
        themeOptionDarkText.updateWhenWindowResize(updateThemeOptionDarkTextPosition());
        themeOptionClassicalText.updateWhenWindowResize(updateThemeOptionClassicalTextPosition());
        themeOptionLightTexture.updateWhenWindowResize(updateThemeOptionLightTexturePosition(), updateThemeOptionLightTextureSize());
        themeOptionDarkTexture.updateWhenWindowResize(updateThemeOptionDarkTexturePosition(), updateThemeOptionDarkTextureSize());
        themeOptionClassicalTexture.updateWhenWindowResize(updateThemeOptionClassicalTexturePosition(), updateThemeOptionClassicalTextureSize());

        fullscreenOptionText.updateWhenWindowResize(updateFullscreenOptionTextPosition());
        fullscreenOptionTexture.updateWhenWindowResize(updateFullscreenOptionTexturePosition(), updateFullscreenOptionTextureSize());
        showFPSOptionText.updateWhenWindowResize(updateShowFPSOptionTextPosition());
        showFPSOptionTexture.updateWhenWindowResize(updateShowFPSOptionTexturePosition(), updateShowFPSOptionTextureSize());
        showMouseTrailOptionText.updateWhenWindowResize(updateShowMouseTrailOptionTextPosition());
        showMouseTrailOptionTexture.updateWhenWindowResize(updateShowMouseTrailOptionTexturePosition(), updateShowMouseTrailOptionTextureSize());
        win7FeatureOptionText.updateWhenWindowResize(updateWin7FeatureOptionTextPosition());
        win7FeatureOptionTexture.updateWhenWindowResize(updateWin7FeatureOptionTexturePosition(), updateWin7FeatureOptionTextureSize());
    }
}

void CPageSettings::render(sf::RenderWindow &window, sf::Event event)
{
    // Preload textures if not loaded yet.
    if (!isTextureLoaded)
    {
        preloadSettingsPageTexture();
    }

    // Draw background with white overlay.
    drawRectangle(window, 0, 0, WindowSizeX, WindowSizeY, sf::Color(255, 255, 255, 255));

    // Draw visual elements.
    // Draw return button.
    if (isMouseStayInArea(window, event, returnButton.area))
        returnButton.scale = 1.1f;
    else
        returnButton.scale = 1.f;
    drawCachedTexture(window, returnButton, settingsPageTexture);

    // Draw theme option light texture.
    if (globalSettings.theme == LIGHT)
        themeOptionLightTexture.path = "page_settings/clicksquare_selected.png";
    else 
        themeOptionLightTexture.path = "page_settings/clicksquare.png";
    drawCachedTexture(window, themeOptionLightTexture, settingsPageTexture);

    // Draw theme option dark texture.
    if (globalSettings.theme == DARK)
        themeOptionDarkTexture.path = "page_settings/clicksquare_selected.png";
    else 
        themeOptionDarkTexture.path = "page_settings/clicksquare.png";
    drawCachedTexture(window, themeOptionDarkTexture, settingsPageTexture);

    // Draw theme option classical texture.
    if (globalSettings.theme == CLASSICAL)
        themeOptionClassicalTexture.path = "page_settings/clicksquare_selected.png";
    else 
        themeOptionClassicalTexture.path = "page_settings/clicksquare.png";
    drawCachedTexture(window, themeOptionClassicalTexture, settingsPageTexture);

    // Draw theme option light text.
    drawText(window, themeOptionLightText);

    // Draw theme option dark text.
    drawText(window, themeOptionDarkText);

    // Draw fullscreen option texture.
    if (globalSettings.fullScreen)
        fullscreenOptionTexture.path = "page_settings/clicksquare_selected.png";
    else
        fullscreenOptionTexture.path = "page_settings/clicksquare.png";
    drawCachedTexture(window, fullscreenOptionTexture, settingsPageTexture);

    // Draw show FPS option texture.
    if (globalSettings.showFPS)
        showFPSOptionTexture.path = "page_settings/clicksquare_selected.png";
    else
        showFPSOptionTexture.path = "page_settings/clicksquare.png";
    drawCachedTexture(window, showFPSOptionTexture, settingsPageTexture);

    // Draw show mouse trail option texture.
    if (globalSettings.showMouseTrail)
        showMouseTrailOptionTexture.path = "page_settings/clicksquare_selected.png";
    else
        showMouseTrailOptionTexture.path = "page_settings/clicksquare.png";
    drawCachedTexture(window, showMouseTrailOptionTexture, settingsPageTexture);

    // Draw win7 feature option texture.
    if (globalSettings.useWin7MineSweeperFeature)
        win7FeatureOptionTexture.path = "page_settings/clicksquare_selected.png";
    else
        win7FeatureOptionTexture.path = "page_settings/clicksquare.png";
    drawCachedTexture(window, win7FeatureOptionTexture, settingsPageTexture);

    // Draw theme option classical text.
    drawText(window, themeOptionClassicalText);

    // Draw fullscreen option text.
    drawText(window, fullscreenOptionText);

    // Draw show FPS option text.
    drawText(window, showFPSOptionText);

    // Draw show mouse trail option text.
    drawText(window, showMouseTrailOptionText);

    // Draw win7 feature option text.
    drawText(window, win7FeatureOptionText);

    // Draw theme text.
    drawText(window, themeText);
}


// Handle back to beginning page.
void CPageSettings::backToBeginning(sf::RenderWindow &window, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    freeSettingsPageTexture();

    currentPage = BEGINNING_PAGE;
}


// Preload settings page texture cache.
void CPageSettings::preloadSettingsPageTexture()
{
    // Preload textures here when needed.
    preloadTexture("page_settings/return.png", settingsPageTexture);
    preloadTexture("page_settings/clicksquare.png", settingsPageTexture);
    preloadTexture("page_settings/clicksquare_selected.png", settingsPageTexture);

    isTextureLoaded = true;
}

void CPageSettings::freeSettingsPageTexture()
{
    // Free texture cache.
    freePreloadTextureCache(settingsPageTexture);

    isTextureLoaded = false;
}