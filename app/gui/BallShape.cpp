#include "BallShape.h"

namespace app { namespace gui {

const unsigned int BallShape::POINTS = 60;

BallShape::BallShape(const BallShape &copy)
    : sf::Drawable(copy), sf::Transformable(copy)
    , radius(copy.radius), texture(copy.texture)
    , colorBg(copy.colorBg), imageBg(copy.imageBg)
{
    imageBg.setTexture(&texture);
}

BallShape::BallShape(float radius, const sf::Color &color, const sf::Image &image)
    : radius(radius), colorBg(0, POINTS), imageBg(0, POINTS)
{
    setRadius(radius);
    texture.loadFromImage(image);
    colorBg.setFillColor(color);
    imageBg.setTexture(&texture);
}

BallShape::~BallShape()
{}

float BallShape::getRadius() const
{
    return radius;
}

void BallShape::setRadius(float radius)
{
    this->radius = radius;

    imageBg.setRadius(radius);
    imageBg.setOrigin(radius, radius);

    radius -= 0.2f; // Render bug fix

    colorBg.setRadius(radius);
    colorBg.setOrigin(radius, radius);
}

void BallShape::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(colorBg, states);
    target.draw(imageBg, states);
}

}};
