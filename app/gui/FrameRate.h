#pragma once

#include <iomanip>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace app { namespace gui {

class FrameRate : public sf::Text
{
private:
    static const int DELAY;

    sf::Clock clock;
    int frames;

public:
    FrameRate();
    FrameRate(const sf::Font &, unsigned int);

    void update();
};

}};
