#include "../include/main.hpp"

// define global game settings parameter.
CGlobalGameSetting globalSettings;

// define global virtual window size parameter.
unsigned int virtualWindowSizeX = 0;
unsigned int virtualWindowSizeY = 0;


int main()
{
    // Show license that give a brife introduction
    showLicense();
    std::cout << "\33[34m[INFO]\33[0m Using debugging terminal." << std::endl;

    // Create the main window for the application and initialize it.
    RenderWindow mainWindow;
    initVisualize(mainWindow, "SweepMine");

    std::vector<TrailPoint> trail;

    /* Page management */
    // Map to store unique pointers to different pages, using C++ features.
    std::map<int, std::unique_ptr<CPage>> pages;
    int currentPage = BEGINNING_PAGE;
    cout << "\33[34m[INFO]\33[0m Current page: " << getPageName(currentPage) << endl;

    // Page Beginning
    pages[BEGINNING_PAGE] = std::make_unique<CPageBeginning>();
    // Page Game
    pages[GAME_PAGE] = std::make_unique<CPageGame>();
    // The following pages are not implemented yet, but will be added in the future.
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
            
            // Check if window size is resized by user and take actions.
            checkWindowResize(mainWindow, event);
            
            // Handle events for the current page if the page exists.
            if (isPageExist(currentPage, pages)) {
                pages[currentPage]->handleEvent(mainWindow, event, currentPage, pages);
            } 
            else {
                cout << "\33[31m[ERROR]\33[0m Page " << getPageName(currentPage) << " does not exist." << endl;
                currentPage = BEGINNING_PAGE;
            }
        }

        // To draw next frame, clear the window.
        mainWindow.clear();

        // Update the current page if it exists.
        if (isPageExist(currentPage, pages)) 
        {
            pages[currentPage]->update(mainWindow, event);
            pages[currentPage]->render(mainWindow, event);
        }
        else 
        {
            cout << "\33[31m[ERROR]\33[0m Page " << getPageName(currentPage) << " does not exist." << endl;
            currentPage = BEGINNING_PAGE;
        }

        // Update mouse trail based on mouse movement. (If showMouseTrail enabled)
        if (globalSettings.showMouseTrail) 
        {
            mouseMoveTrail(event, mainWindow, trail);
            updateTrail(trail, mainWindow);
        }

        // after updating the frame, display the window.
        mainWindow.display();
    }

    // // Pause the app and wait for any input.
    // system("pause");
    return 0;
}
