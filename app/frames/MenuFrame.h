#pragma once

#include "Frame.h"
#include "../gui/SimpleButton.h"
#include "../events/EventListener.h"
#include "../SnookerApplication.h"

namespace app { namespace frames {

class MenuFrame;

class MenuFrame_Press : public events::EventListener
{
public:
    MenuFrame *menu;
    std::string name;

    MenuFrame_Press(MenuFrame *, const std::string &);

    void operator()(const events::Event &);
};

class MenuFrame : public Frame
{
private:
    sf::RectangleShape bg;
    sf::Texture bgTx;

    sf::RectangleShape logo;
    sf::Texture logoTx;

    sf::Texture btnTx;

    gui::SimpleButton newGameBtn;
    MenuFrame_Press newGameBtnL;
    gui::SimpleButton aboutBtn;
    MenuFrame_Press aboutBtnL;
    gui::SimpleButton exitBtn;
    MenuFrame_Press exitBtnL;

    sf::Sound mainSound;

    void updateResized();

public:
    MenuFrame(Application &);

    void buttonPressed(const events::Event &, const std::string &);

    virtual void handleEvent(sf::Event &);
    virtual void draw();
};

}};
