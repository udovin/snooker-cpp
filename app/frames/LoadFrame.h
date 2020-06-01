#pragma once

#include "Frame.h"

#include <string>
#include <SFML/System.hpp>

namespace app { namespace frames {

class LoadFrame : public Frame
{
private:
    static const int DELAY;
    static const std::string FONT;
    static const std::string BG;

    bool bgLoaded;

    int countOfDots;
    sf::Texture bgTexture;
    sf::RectangleShape bg;
    sf::Text text;
    sf::Clock clock;

    sf::Vector2f textBox;

    void updateResized();

public:
    LoadFrame(Application &);
    ~LoadFrame();

    virtual void handleEvent(sf::Event &);
    virtual void draw();

private:
    void update();
};

}};
