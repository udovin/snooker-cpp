#pragma once

#include "data/DataManager.h"

#include <SFML/Graphics.hpp>

namespace app {

class Application
{
private:
    sf::RenderWindow &window;
    data::DataManager dataManager;

public:
    Application(sf::RenderWindow &);
    virtual ~Application();

    sf::RenderWindow &getWindow();
    data::DataManager &getData();

    virtual void handleEvent(sf::Event &) = 0;
    virtual void drawWindow() = 0;
};

};
