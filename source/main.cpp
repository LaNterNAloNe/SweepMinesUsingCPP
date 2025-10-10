#include "../include/main.hpp"


int main() {
    // Show the debugging info in the terminal if needed.
    cout << "\33[36m[INFO]\33[0m Using debugging terminal." << endl;

    int page = BEGINNING_PAGE;

    RenderWindow mainWindow;
    // Initialize the visualization window with specified dimensions and title. Initial height and width is up to user's system resolotion.
    initVisualize(mainWindow, "SweepMine");

    // Vector to store trail points for mouse movement effect.
    std::vector<TrailPoint> trail;

    // Main loop to keep the window open until closed by the user.
    while (mainWindow.isOpen()) {
        Event event;

        // Clear the window at the start of each frame.
        mainWindow.clear();

        // Handle mouse move events to create a trail effect.
        mouseMoveTrail(event, mainWindow, trail);

        switch (page) {
        case BEGINNING_PAGE:
            pageBeginning(mainWindow, event, page);
            break;
        case GAME_PAGE:
            // drawGame(mainWindow);
            break;
        case ENDING_PAGE:
            // drawEnding(mainWindow);
            break;
        default:
            break;
        }
        while (mainWindow.pollEvent(event))
        {
            // Close the window if the close event is triggered.
            if (event.type == Event::Closed)
            {
                mainWindow.close();
            }
            // Debug output for improving code.
            debugOutput(mainWindow, event);
        }
        
        // Draw the trail. Keep it after other drawing and before displaying.
        updateTrail(trail, mainWindow);

        // Display the contents of the window.
        mainWindow.display();
    }


    system("pause");
    return 0;
}