#include "Application.h"

namespace app {

Application::Application(sf::RenderWindow &window)
    : window(window), dataManager()
{}

Application::~Application()
{}

sf::RenderWindow &Application::getWindow()
{
    return window;
}

data::DataManager &Application::getData()
{
    return dataManager;
}

};
