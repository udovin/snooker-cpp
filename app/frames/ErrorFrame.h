#pragma once

#include "Frame.h"

namespace app { namespace frames {

class ErrorFrame : public Frame
{
private:
    sf::Text title, description;
    sf::Font font;

public:
    static const std::string FONT;

    ErrorFrame(Application &);

    virtual void handleEvent(sf::Event &);
    virtual void draw();
};

}};
