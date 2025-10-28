#include "../include/main.hpp"

// Global game settings. Default settings defined here.
GameSettings globalSettings = {LIGHT, false, false, true, false};

// define global virtual window size parameter.
unsigned int WindowSizeX = 0;
unsigned int WindowSizeY = 0;

// Define the valid input regex. (Extern variable)
std::regex validInputRegex("^[a-zA-Z0-9]+$");

int main()
{
    // Show license that give a brife introduction
    showAppInfo();
    cout << "\33[34m[INFO]\33[0m Using debugging terminal." << endl;

    // Create the main window for the application and initialize it.
    RenderWindow mainWindow;
    initVisualize(mainWindow, "Mine Sweeper: A simple game create by C++");
    bool isInWindowedMode = true;

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
    // Page Setting
    pages[SETTING_PAGE] = std::make_unique<CPageSettings>();
    // The following pages are not implemented yet, but will be added in the future. ( If possible :) )
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

        // Adjust window mode based on global settings.
        if (globalSettings.fullScreen && isInWindowedMode)
        {
            // Title is not needed in fullscreen mode.
            setWindowToFullscreen(mainWindow, "");
            isInWindowedMode = false;
        } 
        else if (!globalSettings.fullScreen && !isInWindowedMode)
        {
            setWindowToWindowed(mainWindow, "Mine Sweeper: A simple game create by C++");
            isInWindowedMode = true;
        }
        else ; // No change needed.

        // Display FPS if the setting is enabled.
        if (globalSettings.showFPS)
        {
            displayFPS(mainWindow);
        }

        // after updating the frame, display the window.
        mainWindow.display();
    }

    // // Pause the app and wait for any input.
    // system("pause");
    return 0;
}
