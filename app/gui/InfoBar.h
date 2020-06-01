#pragma once

#include "BallShape.h"
#include "../data/DataManager.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace app { namespace gui {

class InfoBar : public sf::Drawable, public sf::Transformable
{
private:
    sf::Vector2f size;

    // Common
    sf::Texture barBgTx;
    sf::RectangleShape barBg;

    // Players
    sf::Texture playerTx[2];
    sf::RectangleShape player[2];
    sf::Text playerName[2];
    std::vector<BallShape> balls[2];

public:
    InfoBar(data::DataManager &);
    ~InfoBar();

    const sf::Vector2f &getSize() const;

    void addBall(int, const BallShape &);

protected:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};

}};
