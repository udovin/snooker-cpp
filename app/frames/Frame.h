#pragma once

#include "../Application.h"
#include "../data/DataManager.h"

#include <SFML/Graphics.hpp>

namespace app { namespace frames {

class Frame
{
private:
    Application &application;

public:
    Frame(Application &);
    virtual ~Frame();

    Application &getApplication();
    sf::RenderWindow &getWindow();
    data::DataManager &getData();

    virtual void handleEvent(sf::Event &);
    virtual void draw();
};

}};
