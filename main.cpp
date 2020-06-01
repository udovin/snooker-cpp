// Include main configuration
#include "config.h"
#include "app/all.h"

#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
    // Set window size and style
    sf::VideoMode videoMode(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
    sf::Uint32 style = sf::Style::Default/*sf::Style::Titlebar | sf::Style::Close*/;
    sf::ContextSettings contextSettings;

    // Context settings
    contextSettings.antialiasingLevel = 4;

    // Create window
    sf::RenderWindow window(videoMode, APP_NAME, style, contextSettings);

    // Window settings
    window.setVerticalSyncEnabled(true);

    // Create Snooker instance
    app::SnookerApplication application(window);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
            application.handleEvent(event);

        if (window.isOpen())
            application.drawWindow();
    }

    // Exit without any errors
    return APP_EXIT_OK;
}
