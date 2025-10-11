#include "../include/PageBeginning.hpp"

/* Draw begining of the game */
void CPageBeginning::render(sf::RenderWindow &window)
{
    // Draw standard background.
    sf::Color tmpColor = sf::Color::White;
    drawRectangle(window, 0, 0, VIRTUAL_WINDOW_SIZE_X, VIRTUAL_WINDOW_SIZE_Y, tmpColor);

    // Draw a mine at the center of the screen.
    sf::Texture mine;
    drawTextureWithPath(window, VIRTUAL_WINDOW_SIZE_X / 2, VIRTUAL_WINDOW_SIZE_Y / 2 - 100, 150, mine, "page_beginning/mine.png");

    // Draw a "Start Game" button at the center of the screen.
    sf::Font font;
    drawText(window, VIRTUAL_WINDOW_SIZE_X / 2, VIRTUAL_WINDOW_SIZE_Y / 2 + 100, 40, "Start Game", sf::Color::Black, CENTER);

    // Draw a "Exit" button at the center of the screen.
    drawTextureWithPath(window, exitButtonX, exitButtonY, exitButtonSize, mine, "page_beginning/exit.png");
}

/* Update beginning page */
void CPageBeginning::update(sf::RenderWindow &window)
{
    // Currently, no dynamic content to update on the beginning page.
}

/* Handle events on the beginning page */
void CPageBeginning::handleEvent(sf::RenderWindow &window, sf::Event &event)
{
    // Check if the "Start Game" button is clicked.
    if (isMouseClickInArea(window, event, exitButtonArea) == LEFTCLICK)
    {
        cout << "\33[34m[INFO]\33[0m " << getPageName(BEGINNING_PAGE) << " 'Exit' button clicked." << endl;
        window.close();
        cout << "\33[34m[INFO]\33[0m Exiting game." << endl;
    }
}
