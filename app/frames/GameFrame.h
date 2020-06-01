#pragma once

#include "Frame.h"
#include "../gui/all.h"

#include <iostream>

namespace app { namespace frames {

struct _BallInfo
{
    float x, y;
    sf::Color color;
};

struct _BoardInfo
{
    float x, y;
    float w, h;
};

class GameFrame : public Frame
{
private:
    static const int BALLS_COUNT;
    static const _BallInfo BALLS[];
    static const int BOARDS_COUNT;
    static const _BoardInfo BOARDS[];

    /*
     * -1 - unknown
     * 0 - first player
     * 1 - second player
     */
    int playerTurn;

    /*
     * true if player can hit the ball
     * false otherwise
     */
    bool playerHit;

    /*
     * -1 - unknown
     * 0 - color
     * 1 - red
     * 2 - yellow
     * 3 - green
     * 4 - brown
     * 5 - blue
     * 6 - pink
     * 7 - black
     */
    int playerBall;

    phys::Body *whiteBall;

    gui::FrameRate frameRate;

    sf::Texture gameBgTx;
    sf::RectangleShape gameBg;

    sf::Texture cueTx;
    sf::RectangleShape cue;

    gui::InfoBar infoBar;
    gui::GameTable table;

    bool mousePressed;
    phys::math::Vector2 mouseLastPos;

    sf::Sound kickSound;

public:
    GameFrame(Application &);

    virtual void handleEvent(sf::Event &);
    virtual void draw();

private:
    void startNewGame(int = 0);
};

}};
