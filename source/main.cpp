#include "../include/main.hpp"


int main() {
    // Show the debugging info in the terminal if needed.
    cout << "\33[36m[INFO]\33[0m Using debugging terminal." << endl;

    RenderWindow mainWindow;
    // Initialize the visualization window with specified dimensions and title. Initial height and width is up to user's system resolotion.
    initVisualize(mainWindow, "SweepMine");
    std::vector<TrailPoint> trail;

    // Main loop to keep the window open until closed by the user.
    while (mainWindow.isOpen()) {
        Event event;

        while (mainWindow.pollEvent(event)) {
            // Handle mouse move events to create a trail effect.
            mouseMoveTrail(event, mainWindow, trail);
            if (event.type == Event::MouseButtonPressed) {
                cout << "\33[32m[DEBUG]\33[0m Mouse button pressed at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")." << endl;
            }

            // Close the window if the close event is triggered.
            if (event.type == Event::Closed) {
                mainWindow.close();
            }
        }

        // Clear the window with a black background.
        mainWindow.clear();

        // Draw the trail.
        updateTrail(trail, mainWindow);

        // Display the contents of the window.
        mainWindow.display();
    }


    system("pause");
    return 0;
}