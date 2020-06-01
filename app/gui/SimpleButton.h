#pragma once

#include "../events/EventDispatcher.h"

#include <cmath>
#include <SFML/Graphics.hpp>

namespace app { namespace gui {

class SimpleButton
    : public events::EventDispatcher, public sf::Drawable, public sf::Transformable
{
private:
    static const unsigned MOUSE_ON;
    static const unsigned PRESSED;

    sf::RectangleShape background;
    sf::Text text;

    sf::Vector2f size;

    unsigned state;

    void update();

public:
    SimpleButton();

    void setHandler();

    void handleEvent(const sf::Event &);

    void setSize(float, float);
    const sf::Vector2f &getSize() const;

    void setBackground(const sf::Color &);

    void setTexture(const sf::Texture &);

    void setCharacterSize(float);

    void setFont(const sf::Font &);

    void setString(const sf::String &);

    void setColor(const sf::Color &);

protected:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};

}};
