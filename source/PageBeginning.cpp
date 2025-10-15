#include "../include/PageBeginning.hpp"

/* Handle events on the beginning page */
void CPageBeginning::handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    // Check if the "Exit" button is clicked.
    if (isMouseClickInArea(window, event, exitButtonTexture.area) == LEFTCLICK)
    {
        cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Exit' button clicked." << endl;
        window.close();
        cout << "\33[34m[INFO]\33[0m Exiting game." << endl;
    }
    // Check if the "Start Game" button is clicked.
    else if (isMouseClickInArea(window, event, startGameButtonText.area) == LEFTCLICK)
    {
        cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Start Game' button clicked." << endl;
        changePage(window, currentPage, GAME_PAGE, pages);
    }
}



/* Update beginning page */
void CPageBeginning::update(sf::RenderWindow &window, sf::Event event)
{
        

    // React to window resizing.
    if (event.type == sf::Event::Resized || lastWindowSize != static_cast<sf::Vector2f>(window.getSize()))
    {
        // Update the lastWindowSize parameter in this page class.
        lastWindowSize = static_cast<sf::Vector2f>(window.getSize());

        // Update the position of the text objects.
        mineTexture.updateWhenWindowResize(updateMineTexturePosition(), updateMineTextureSize());
        startGameButtonText.updateWhenWindowResize(updateStartGameButtonTextPosition());
        exitButtonTexture.updateWhenWindowResize(updateExitTexturePosition(), updateExitTextureSize());
        exitButtonTextureHover.updateWhenWindowResize(updateExitTexturePosition(), updateExitTextureSize());
        exitButtonText.updateWhenWindowResize(updateExitTextPosition());
    }

    if (!isTextureLoaded)
    {
        preloadBeginningPageTexture();
    }
}



/* Draw begining of the game */
void CPageBeginning::render(sf::RenderWindow &window, sf::Event event)
{
    // Draw standard background.
    sf::Color tmpColor = sf::Color::White;
    drawRectangle(window, 0, 0, WindowSizeX, WindowSizeY, tmpColor);

    // Draw a mine at the center of the screen.
    drawCachedTexture(window, mineTexture, beginningPageTexture);

    // Draw a "Start Game" button at the center of the screen.
    if (isMouseStayInArea(window, event, startGameButtonText.area))
        startGameButtonText.textObject.setScale(1.1f, 1.1f);
    else
        startGameButtonText.textObject.setScale(1.f, 1.f);
    drawText(window, startGameButtonText);

    // Draw a "Exit" button at the center of the screen.
    drawCachedTexture(window, isMouseStayInArea(window, event, exitButtonTexture.area) ? exitButtonTextureHover : exitButtonTexture, beginningPageTexture);

    // Draw Exit button color
    exitButtonText.textObject.setFillColor(isMouseStayInArea(window, event, exitButtonTexture.area) ? sf::Color::Black : sf::Color::Transparent);
    drawText(window, exitButtonText);
}


void CPageBeginning::preloadBeginningPageTexture()
{
    // Load texture of the beginning page.
    preloadTexture("page_beginning/exit.png", beginningPageTexture);
    preloadTexture("page_beginning/exit_hover.png", beginningPageTexture);
    preloadTexture("page_beginning/mine.png", beginningPageTexture);

    isTextureLoaded = true;
}

void CPageBeginning::freeBeginningPageTexture()
{
    // Free texture of the beginning page.
    freePreloadTextureCache(beginningPageTexture);

    isTextureLoaded = false;
}