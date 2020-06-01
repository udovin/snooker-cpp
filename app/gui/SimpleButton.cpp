#include "SimpleButton.h"

namespace app { namespace gui {

const unsigned SimpleButton::MOUSE_ON = 0b0001;
const unsigned SimpleButton::PRESSED  = 0b0010;

SimpleButton::SimpleButton()
    : background(), text(), state(0)
{}

void SimpleButton::update()
{
    background.setPosition(0, 0);
    background.setOrigin(0, 0);

    // floor - font blur bug fix
    text.setPosition(
        floor((size.x - text.getLocalBounds().width) / 2),
        floor((size.y - text.getLocalBounds().height) / 2));

    text.setOrigin(
        text.getLocalBounds().left,
        text.getLocalBounds().top);

    background.setSize(size);
}

void SimpleButton::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f mousePos(
            event.mouseMove.x - getPosition().x,
            event.mouseMove.y - getPosition().y);

        if (background.getGlobalBounds().contains(mousePos))
        {
            if ((state & MOUSE_ON) == 0)
            {
                state = state | MOUSE_ON;
                dispatchEvent(events::Event("on"));
            }
        }
        else if ((state & MOUSE_ON) != 0)
        {
            state = state ^ MOUSE_ON;
            dispatchEvent(events::Event("over"));
        }
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(
            event.mouseButton.x - getPosition().x,
            event.mouseButton.y - getPosition().y);

        if (background.getGlobalBounds().contains(mousePos))
        {
            state = state | PRESSED;
            dispatchEvent(events::Event("pressed"));
        }
        else if ((state & PRESSED) != 0)
            state = state ^ PRESSED;
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        sf::Vector2f mousePos(
            event.mouseButton.x - getPosition().x,
            event.mouseButton.y - getPosition().y);

        if ((state & PRESSED) != 0)
        {
            state = state ^ PRESSED;
            dispatchEvent(events::Event("released"));
        }
    }
}

void SimpleButton::setSize(float width, float height)
{
    size.x = width, size.y = height;

    update();
}

const sf::Vector2f &SimpleButton::getSize() const
{
    return size;
}

void SimpleButton::setBackground(const sf::Color &color)
{
    background.setFillColor(color);
}

void SimpleButton::setTexture(const sf::Texture &texture)
{
    background.setTexture(&texture);
}

void SimpleButton::setCharacterSize(float size)
{
    text.setCharacterSize(size);

    update();
}

void SimpleButton::setFont(const sf::Font &font)
{
    text.setFont(font);

    update();
}

void SimpleButton::setString(const sf::String &str)
{
    text.setString(str);

    update();
}

void SimpleButton::setColor(const sf::Color &color)
{
    text.setColor(color);

    update();
}

void SimpleButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(background, states);
    target.draw(text, states);
}

}};
