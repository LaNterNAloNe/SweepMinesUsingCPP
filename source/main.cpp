#include "../include/main.hpp"

int main()
{
    // Show license that give a brife introduction
    showLicense();
    std::cout << "\33[34m[INFO]\33[0m Using debugging terminal." << std::endl;

    // Create the main window for the application and initialize it.
    RenderWindow mainWindow;
    initVisualize(mainWindow, "SweepMine");

    std::vector<TrailPoint> trail;
    int currentPage = BEGINNING_PAGE;
    cout << "\33[34m[INFO]\33[0m Current page: " << getPageName(currentPage) << endl;

    /* Page management */
    // Map to store unique pointers to different pages, using C++ features.
    std::map<int, std::unique_ptr<CPage>> pages;
    pages[BEGINNING_PAGE] = std::make_unique<CPageBeginning>();
    // The following pages are not implemented yet, but will be added in the future.
    // pages[GAME_PAGE] = std::make_unique<CPageGame>();
    // pages[ENDING_PAGE] = std::make_unique<CPageEnding>();

    /* Main game loop */
    while (mainWindow.isOpen())
    {
        // Event object to hold events.
        sf::Event event;

        // Event handling. If there are multiple events, they would be handled one by one.
        while (mainWindow.pollEvent(event))
        {
            // Close window event
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
                 cout << "\33[34m[INFO]\33[0m window closed." << endl;
            }

            // Debug output for multiple types of events.
            debugOutput(mainWindow, event);
            // Handle events for the current page if the page exists.
            if (isPageExist(currentPage, pages)) {
                pages[currentPage]->handleEvent(mainWindow, event);
            }
        }

        // To draw next frame, clear the window.
        mainWindow.clear();

        // Update the current page if it exists.
        if (isPageExist(currentPage, pages)) {
            pages[currentPage]->update(mainWindow);
            pages[currentPage]->render(mainWindow);
        }

        // Update mouse trail based on mouse movement.
        mouseMoveTrail(event, mainWindow, trail);
        updateTrail(trail, mainWindow);

        // after updating the frame, display the window.
        mainWindow.display();
    }

    // Pause the app and wait for any input.
    system("pause");
    return 0;
}
