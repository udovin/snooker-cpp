#include "GameTable.h"
#include <iostream>

namespace app { namespace gui {

GameTable::GameTable(data::DataManager &data)
    : world(), balls(), staying(true)
{
    tableBgTx.loadFromImage(data.getImage("table_bg"));
    tableBgTx.setSmooth(true);
    tableBg.setTexture(&tableBgTx);
    tableBg.setSize(sf::Vector2f(960, 500));
}

GameTable::~GameTable()
{}

void GameTable::update()
{
    bool canStaying = true;

    // Update world
    world.step(clock.getElapsedTime().asSeconds(), 30), clock.restart();

    // Update positions
    for (std::size_t i = 0; i < balls.size(); i++)
    {
        if (balls[i].second->getLinearVelocity().lengthSquared() > VELOCITY_EPS)
            canStaying = false;

        //balls[i].second->setLinearVelocity(vel - vel.unit() * mass * 10 * dt);
        phys::math::Vector2 pos = balls[i].second->getPosition();
        float angle = balls[i].second->getAngle();
        balls[i].first.setPosition(sf::Vector2f(pos.x, pos.y));
        // Only for debug
        balls[i].first.setRotation(angle * 180 / 3.14159265);
    }

    staying = canStaying;
}

void GameTable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(tableBg, states);

    for (std::size_t i = 0; i < balls.size(); i++)
        target.draw(balls[i].first, states);
}

}};
