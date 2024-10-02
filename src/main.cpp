#include <SFML/Graphics.hpp>
#include <windows.h>
#include <sstream>
#include "include/WindowMover.hpp"

int main() {
    // Create a window with no title bar and enable alpha channel
    sf::RenderWindow window(sf::VideoMode(200, 200), "Ball", sf::Style::None, sf::ContextSettings(0, 0, 0, 0, 0, sf::ContextSettings::Core));
    sf::Clock clock; // Create a clock to track the elapsed time
    WindowMover windowMover(0.5f, .8f, .9f); // Create a window mover object with gravity effect

    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    // Enable transparency
    HWND hwnd = window.getSystemHandle();
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    while (window.isOpen()) {
        sf::Event event;

        float deltaTime = clock.restart().asSeconds() * 60; // Restart the clock and get the elapsed time

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            windowMover.handleEvent(event, window, deltaTime); // Handle window dragging events
        }

        windowMover.update(window, deltaTime); // Update the window position every frame

        window.clear(sf::Color::Transparent); // Clear the window with transparent color
        windowMover.draw(window); // Draw a red circle
        window.display(); // Display the updated window
    }

    return 0;
}