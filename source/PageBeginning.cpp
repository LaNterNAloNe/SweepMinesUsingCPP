#include "../include/PageBeginning.hpp"

/* Handle events on the beginning page */
void CPageBeginning::handleEvent(sf::RenderWindow &window, sf::Event &event, int &currentPage, const std::map<int, std::unique_ptr<CPage>> &pages)
{
    // Check if the "Exit" button is hovered.
    if (isMouseStayInArea(window, event, exitButtonArea))
    {
        currentHoverState = EXIT;
    }
    // Check if the "Start Game" button is hovered.
    else if (isMouseStayInArea(window, event, makeTextArea(startGameButtonText)))
    {
        currentHoverState = START_GAME;
    }
    else
    {
        currentHoverState = NONE;
    }

    // Check if the "Start Game" button is clicked.
    if (isMouseClickInArea(window, event, exitButtonArea) == LEFTCLICK)
    {
        cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Exit' button clicked." << endl;
        window.close();
        cout << "\33[34m[INFO]\33[0m Exiting game." << endl;
    }
    else if (isMouseClickInArea(window, event, makeTextArea(startGameButtonText)) == LEFTCLICK)
    {
        cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Start Game' button clicked." << endl;
        changePage(window, currentPage, GAME_PAGE, pages);
    }
}



/* Update beginning page */
void CPageBeginning::update(sf::RenderWindow &window)
{
    static hoverState lastHoverState = NONE;

    if (currentHoverState != lastHoverState)
    {
        // Update Start Game button scale
        startGameButtonText.setScale(currentHoverState == START_GAME ? 0.9f : 1.f,
                                     currentHoverState == START_GAME ? 0.9f : 1.f);

        // Update Exit button color
        exitButtonText.setFillColor(currentHoverState == EXIT ? sf::Color::Black : sf::Color::Transparent);

        lastHoverState = currentHoverState;
    }
}



/* Draw begining of the game */
void CPageBeginning::render(sf::RenderWindow &window)
{
    // Draw standard background.
    sf::Color tmpColor = sf::Color::White;
    drawRectangle(window, 0, 0, VIRTUAL_WINDOW_SIZE_X, VIRTUAL_WINDOW_SIZE_Y, tmpColor);

    // Draw a mine at the center of the screen.
    drawTextureWithPath(window, VIRTUAL_WINDOW_SIZE_X / 2, VIRTUAL_WINDOW_SIZE_Y / 2 - 100, 150, "page_beginning/mine.png");

    // Draw a "Start Game" button at the center of the screen.
    drawText(window, startGameButtonText);

    // Draw a "Exit" button at the center of the screen.
    drawTextureWithPath(window, exitButtonX, exitButtonY, exitButtonSize,
                        currentHoverState == EXIT ? "page_beginning/exit_hover.png" : "page_beginning/exit.png");
    drawText(window, exitButtonText);
}
