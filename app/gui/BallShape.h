#pragma once

#include <SFML/Graphics.hpp>

namespace app { namespace gui {

class BallShape : public sf::Drawable, public sf::Transformable
{
private:
    static const unsigned int POINTS;

    float radius;
    sf::Texture texture;
    sf::CircleShape colorBg, imageBg;

public:
    BallShape(const BallShape &);
    BallShape(float, const sf::Color &, const sf::Image &);
    ~BallShape();

    float getRadius() const;
    void setRadius(float);

protected:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};

}};
