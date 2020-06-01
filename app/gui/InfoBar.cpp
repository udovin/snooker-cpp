#include "InfoBar.h"

namespace app { namespace gui {

InfoBar::InfoBar(data::DataManager &data)
    : size(980, 130)
{
    barBgTx.loadFromImage(data.getImage("info_bar"));
    barBg.setTexture(&barBgTx);
    barBg.setSize(sf::Vector2f(980, 130));
    barBg.setPosition(sf::Vector2f(0, 0));

    for (int i = 0; i < 2; i++)
    {
        playerTx[i].loadFromImage(data.getImage("player"));

        std::string playerStr = "Player ";
        playerStr.push_back('1' + i);

        player[i].setTexture(&playerTx[i]);
        player[i].setSize(sf::Vector2f(90, 90));
        player[i].setPosition(sf::Vector2f(
            15 + i * (950 - player[i].getSize().x),
            25
        ));

        playerName[i].setFont(data.getFont("helvetica"));
        playerName[i].setCharacterSize(16);
        playerName[i].setString(playerStr);
        playerName[i].setPosition(sf::Vector2f(
            120 + i * (740 - playerName[i].getLocalBounds().width),
            20
        ));
    }
}

InfoBar::~InfoBar()
{}

const sf::Vector2f &InfoBar::getSize() const
{
    return size;
}

void InfoBar::addBall(int id, const BallShape &ball)
{
    balls[id].push_back(ball);
    BallShape &curr = balls[id].back();
    float radius = curr.getRadius();
    int row = (balls[id].size() - 1) % 20;
    int col = (balls[id].size() - 1) / 20;

    if (id == 0)
    {
        curr.setPosition(sf::Vector2f(
            120 + radius + row * radius,
            76 - curr.getRadius() + col * (radius * 2 + 6)
        ));
    }
    else
    {
        curr.setPosition(sf::Vector2f(
            860 - curr.getRadius() - row * radius,
            76 - curr.getRadius() + col * (radius * 2 + 6)
        ));
    }
}

void InfoBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(barBg, states);
    for (int i = 0; i < 2; i++)
    {
        target.draw(player[i], states);
        target.draw(playerName[i], states);
        for (std::size_t j = 0; j < balls[i].size(); j++)
        {
            target.draw(balls[i][j], states);
        }
    }
}

}};
