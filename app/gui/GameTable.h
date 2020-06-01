#pragma once

#include "BallShape.h"
#include "../data/DataManager.h"
#include "../../phys/all.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace app { namespace gui {

class GameTable : public sf::Drawable, public sf::Transformable
{
private:
    static const float VELOCITY_EPS = 0.5f;

    sf::Clock clock;

    sf::Texture tableBgTx;
    sf::RectangleShape tableBg;

public:
    typedef std::pair<BallShape, phys::Body *> BallPair;

    phys::World world;
    std::vector<BallPair> balls;

    bool staying;

    GameTable(data::DataManager &);
    ~GameTable();

    void update();

protected:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
};

}};
