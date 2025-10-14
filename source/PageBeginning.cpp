#include "../include/PageBeginning.hpp"

/* Handle events on the beginning page */
void CPageBeginning::handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    // Check if the "Exit" button is hovered.
    if (isMouseStayInArea(window, event, exitButtonTexture.area))
    {
        currentHoverState = EXIT;
    }
    // Check if the "Start Game" button is hovered.
    else if (isMouseStayInArea(window, event, startGameButtonText.area))
    {
        currentHoverState = START_GAME;
    }
    else
    {
        currentHoverState = NONE;
    }

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
    static hoverState lastHoverState = NONE;

    if (currentHoverState != lastHoverState)
    {
        // Update Start Game button scale
        startGameButtonText.textObject.setScale(currentHoverState == START_GAME ? 0.9f : 1.f,
                                     currentHoverState == START_GAME ? 0.9f : 1.f);

        // Update Exit button color
        exitButtonText.textObject.setFillColor(currentHoverState == EXIT ? sf::Color::Black : sf::Color::Transparent);

        lastHoverState = currentHoverState;
    }

    // React to window resizing.
    if (event.type == sf::Event::Resized)
    {
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
    drawRectangle(window, 0, 0, virtualWindowSizeX, virtualWindowSizeY, tmpColor);

    // Draw a mine at the center of the screen.
    drawTextureWithPath(window, mineTexture);

    // Draw a "Start Game" button at the center of the screen.
    drawText(window, startGameButtonText.textObject);

    // Draw a "Exit" button at the center of the screen.
    drawTextureWithPath(window, currentHoverState == EXIT ? exitButtonTextureHover : exitButtonTexture);
    drawText(window, exitButtonText.textObject);

    // DEBUG
    showRect(window, exitButtonTexture.area);
    showRect(window, exitButtonText.area);
    showRect(window, startGameButtonText.area);
    // showLine(window, {0, 0}, updateExitTexturePosition());
    // showLine(window, {0, virtualWindowSizeY}, updateExitTextPosition());
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