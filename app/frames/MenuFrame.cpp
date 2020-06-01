#include "MenuFrame.h"
#include <iostream>

namespace app { namespace frames {

MenuFrame_Press::MenuFrame_Press(MenuFrame *menu, const std::string &name)
    : menu(menu), name(name)
{}

void MenuFrame_Press::operator()(const events::Event &event)
{
    menu->buttonPressed(event, name);
}

MenuFrame::MenuFrame(Application &application)
    : Frame(application), newGameBtnL(this, "new_game")
    , aboutBtnL(this, "about"), exitBtnL(this, "exit")
{
    // Set background
    bgTx.loadFromImage(getData().getImage("menu_bg"));
    bgTx.setSmooth(true);

    bg.setTexture(&bgTx);
    bg.setFillColor(sf::Color::White);

    // Set logo
    logoTx.loadFromImage(getData().getImage("logo"));
    logoTx.setSmooth(true);

    logo.setTexture(&logoTx);
    logo.setFillColor(sf::Color::White);
    logo.setSize(sf::Vector2f(584, 162));

    // Buttons texture
    btnTx.loadFromImage(getData().getImage("button_bg"));
    btnTx.setSmooth(true);

    // New game button
    newGameBtn.setFont(getData().getFont("helvetica"));
    newGameBtn.setSize(210, 60);
    newGameBtn.setCharacterSize(26);
    newGameBtn.setString("New game");
    newGameBtn.setColor(sf::Color::Black);
    newGameBtn.setTexture(btnTx);

    // About button
    aboutBtn.setFont(getData().getFont("helvetica"));
    aboutBtn.setSize(210, 60);
    aboutBtn.setCharacterSize(26);
    aboutBtn.setString("About");
    aboutBtn.setColor(sf::Color::Black);
    aboutBtn.setTexture(btnTx);

    // Exit button
    exitBtn.setFont(getData().getFont("helvetica"));
    exitBtn.setSize(210, 60);
    exitBtn.setCharacterSize(26);
    exitBtn.setString("Exit");
    exitBtn.setColor(sf::Color::Black);
    exitBtn.setTexture(btnTx);

    // Sound
    mainSound.setBuffer(getData().getSound("music_1"));
    mainSound.setLoop(true);
    mainSound.play();

    // Button press events
    newGameBtn.addEventListener("released", &newGameBtnL);
    aboutBtn.addEventListener("released", &aboutBtnL);
    exitBtn.addEventListener("released", &exitBtnL);

    // Update sizes of elements
    updateResized();
}

void MenuFrame::buttonPressed(const events::Event &event, const std::string &btnType)
{
    if (event.type == "released")
    {
        if (btnType == "new_game")
            dynamic_cast<SnookerApplication &>(getApplication()).wantToggleGameFrame();

        if (btnType == "exit")
            getWindow().close();
    }
}

void MenuFrame::updateResized()
{
    bg.setPosition(0, 0);
    bg.setSize(static_cast<sf::Vector2f>(getWindow().getSize()));

    logo.setPosition(
        (getWindow().getSize().x - logo.getSize().x) / 2,
        getWindow().getSize().y / 2 - 220);

    newGameBtn.setPosition(
        (getWindow().getSize().x - newGameBtn.getSize().x) / 2,
        getWindow().getSize().y / 2 + 20);

    aboutBtn.setPosition(
        (getWindow().getSize().x - aboutBtn.getSize().x) / 2,
        getWindow().getSize().y / 2 + 100);

    exitBtn.setPosition(
        (getWindow().getSize().x - exitBtn.getSize().x) / 2,
        getWindow().getSize().y / 2 + 180);
}

void MenuFrame::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::Resized)
        updateResized();

    newGameBtn.handleEvent(event);
    aboutBtn.handleEvent(event);
    exitBtn.handleEvent(event);
}

void MenuFrame::draw()
{
    getWindow().draw(bg);
    getWindow().draw(logo);

    // Add buttons
    getWindow().draw(newGameBtn);
    getWindow().draw(aboutBtn);
    getWindow().draw(exitBtn);
}

}};
