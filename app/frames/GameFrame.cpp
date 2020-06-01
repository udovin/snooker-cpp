#include "GameFrame.h"

namespace app { namespace frames {

const int GameFrame::BALLS_COUNT = 22;

const _BallInfo GameFrame::BALLS[] = {
    (_BallInfo){780, 212, sf::Color::White       }, // White
    (_BallInfo){750, 174, sf::Color::Yellow      }, // Yellow
    (_BallInfo){750, 326, sf::Color::Green       }, // Green
    (_BallInfo){750, 250, sf::Color(150, 75, 0)  }, // Brown
    (_BallInfo){480, 250, sf::Color::Blue        }, // Blue
    (_BallInfo){250, 250, sf::Color(252, 15, 192)}, // Pink
    (_BallInfo){104, 250, sf::Color::Black       }, // Black
    (_BallInfo){230, 250, sf::Color::Red         }, // Red
    (_BallInfo){213, 240, sf::Color::Red         }, // Red
    (_BallInfo){213, 260, sf::Color::Red         }, // Red
    (_BallInfo){196, 230, sf::Color::Red         }, // Red
    (_BallInfo){196, 250, sf::Color::Red         }, // Red
    (_BallInfo){196, 270, sf::Color::Red         }, // Red
    (_BallInfo){179, 220, sf::Color::Red         }, // Red
    (_BallInfo){179, 240, sf::Color::Red         }, // Red
    (_BallInfo){179, 260, sf::Color::Red         }, // Red
    (_BallInfo){179, 280, sf::Color::Red         }, // Red
    (_BallInfo){162, 210, sf::Color::Red         }, // Red
    (_BallInfo){162, 230, sf::Color::Red         }, // Red
    (_BallInfo){162, 250, sf::Color::Red         }, // Red
    (_BallInfo){162, 270, sf::Color::Red         }, // Red
    (_BallInfo){162, 290, sf::Color::Red         }  // Red
};

const int GameFrame::BOARDS_COUNT = 6;

const _BoardInfo GameFrame::BOARDS[] = {
    (_BoardInfo){10, 250, 20, 428},
    (_BoardInfo){950, 250, 20, 428},
    (_BoardInfo){250, 10, 428, 20},
    (_BoardInfo){710, 10, 428, 20},
    (_BoardInfo){250, 490, 428, 20},
    (_BoardInfo){710, 490, 428, 20}
};

GameFrame::GameFrame(Application &application)
    : Frame(application)
    , playerTurn(-1), playerHit(false), playerBall(-1)
    , frameRate(getData().getFont("consolas"), 16)
    , infoBar(getData()), table(getData())
    , mousePressed(false)
{
    frameRate.setPosition(sf::Vector2f(5, 5));
    frameRate.setColor(sf::Color::White);

    gameBgTx.loadFromImage(getData().getImage("game_bg"));
    gameBgTx.setRepeated(true);
    gameBg.setTexture(&gameBgTx);
    gameBg.setTextureRect(sf::IntRect(
        0, 0,
        getWindow().getSize().x, getWindow().getSize().y
    ));
    gameBg.setSize(sf::Vector2f(
        getWindow().getSize().x, getWindow().getSize().y
    ));

    cueTx.loadFromImage(getData().getImage("cue"));
    cue.setTexture(&cueTx);
    cue.setSize(sf::Vector2f(600, 48));
    cue.setOrigin(sf::Vector2f(10, 24));

    infoBar.setPosition(sf::Vector2f(
        0,
        getWindow().getSize().y - infoBar.getSize().y
    ));

    table.setPosition(sf::Vector2f(10, 10));

    kickSound.setBuffer(getData().getSound("kick"));

    // Start game
    startNewGame();
}

void GameFrame::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        mouseLastPos.set(
            event.mouseButton.x - 10, event.mouseButton.y - 10
        );
        mousePressed = true;
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (playerHit && mousePressed)
        {
            phys::math::Vector2 mouseCurrPos(
                event.mouseButton.x - 10, event.mouseButton.y - 10
            );
            float angle = atan2(
                mouseCurrPos.y - whiteBall->getPosition().y,
                mouseCurrPos.x - whiteBall->getPosition().x
            );
            float lastRad = mouseLastPos.distance(whiteBall->getPosition());
            float currRad = mouseCurrPos.distance(whiteBall->getPosition());
            float dr = std::min(std::max(currRad - lastRad, 0.0f), 64.0f);
            if (dr > 2.0f)
            {
                kickSound.stop();
                kickSound.setVolume(100 * (dr / 60));
                kickSound.play();
                phys::math::Vector2 newVelocity(
                    dr * cos(angle), dr * sin(angle)
                );
                whiteBall->setLinearVelocity(-newVelocity * 8.0f);
                cue.setOrigin(sf::Vector2f(10, 24));
                playerHit = false;
            }
        }
        mousePressed = false;
    }

    if (event.type == sf::Event::MouseMoved)
    {
        if (playerHit && mousePressed)
        {
            phys::math::Vector2 mouseCurrPos(
                event.mouseMove.x - 10, event.mouseMove.y - 10
            );
            float angle = atan2(
                mouseCurrPos.y - whiteBall->getPosition().y,
                mouseCurrPos.x - whiteBall->getPosition().x
            );
            float lastRad = mouseLastPos.distance(whiteBall->getPosition());
            float currRad = mouseCurrPos.distance(whiteBall->getPosition());
            float dr = std::min(std::max(currRad - lastRad, 0.0f), 64.0f);
            cue.setOrigin(sf::Vector2f(10 - dr, 24));
            cue.setRotation(angle * 180 / 3.14159265);
        }
    }
}

void GameFrame::draw()
{
    // Update frame rate
    frameRate.update();

    // Update table
    table.update();

    if (!playerHit && table.staying)
    {
        playerHit = true;
    }

    // Draw elements
    getWindow().draw(gameBg);
    getWindow().draw(table);

    // Draw cue
    if (playerHit)
    {
        cue.setPosition(sf::Vector2f(
            whiteBall->getPosition().x + 10,
            whiteBall->getPosition().y + 10
        ));
        getWindow().draw(cue);
        sf::Vertex line[] =
        {
            sf::Vertex(cue.getPosition()),
            sf::Vertex(sf::Vector2f(
                cue.getPosition().x - 980 * cos(cue.getRotation() / 180 * 3.14159265),
                cue.getPosition().y - 980 * sin(cue.getRotation() / 180 * 3.14159265)
            ))
        };
        getWindow().draw(line, 2, sf::Lines);
    }

    // Draw info bar
    getWindow().draw(infoBar);

    // Draw frame rate
    getWindow().draw(frameRate);
}

void GameFrame::startNewGame(int turn)
{
    std::cerr << "Starting new game..." << std::endl;

    for (int i = 0; i < BALLS_COUNT; i++) {
        gui::BallShape ballShape(10.0f, BALLS[i].color, getData().getImage("ball"));

        phys::BodyDef bodyDef;
        bodyDef.type = phys::Body::DYNAMIC;
        bodyDef.position.set(BALLS[i].x, BALLS[i].y);
        bodyDef.mass = 10.0f;
        bodyDef.restitution = 0.96f;
        bodyDef.shape = new phys::shapes::Circle(10.0f);
        //bodyDef.linearDamping = 0.5f;
        bodyDef.linearDamping = 64.0f;
        phys::Body *ballBody = table.world.createBody(bodyDef);

        gui::GameTable::BallPair ballPair(ballShape, ballBody);

        table.balls.push_back(ballPair);
    }

    for (int i = 0; i < BOARDS_COUNT; i++) {
        phys::BodyDef bodyDef;
        bodyDef.type = phys::Body::STATIC;
        bodyDef.position.set(BOARDS[i].x, BOARDS[i].y);
        bodyDef.restitution = 0.95f;
        phys::shapes::Polygon *polygon;
        polygon = new phys::shapes::Polygon;
        float w2 = BOARDS[i].w / 2, h2 = BOARDS[i].h / 2;
        polygon->vertices.push_back(phys::math::Vector2(-w2 + 7, -h2));
        polygon->vertices.push_back(phys::math::Vector2(+w2 - 7, -h2));
        polygon->vertices.push_back(phys::math::Vector2(+w2, -h2 + 7));
        polygon->vertices.push_back(phys::math::Vector2(+w2, +h2 - 7));
        polygon->vertices.push_back(phys::math::Vector2(+w2 - 7, +h2));
        polygon->vertices.push_back(phys::math::Vector2(-w2 + 7, +h2));
        polygon->vertices.push_back(phys::math::Vector2(-w2, +h2 - 7));
        polygon->vertices.push_back(phys::math::Vector2(-w2, -h2 + 7));
        bodyDef.shape = polygon;
        table.world.createBody(bodyDef);
    }

    whiteBall = table.balls.front().second;

    playerTurn = turn;
    playerHit = true;
    playerBall = 1;

    mousePressed = false;
}

}};
