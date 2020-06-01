#include "LoadFrame.h"

namespace app { namespace frames {

const int LoadFrame::DELAY = 150;
const std::string LoadFrame::FONT = "nautilus";
const std::string LoadFrame::BG = "loading_bg";

LoadFrame::LoadFrame(Application &application)
    : Frame(application), bgLoaded(false), countOfDots(0), clock()
{
    // Set background
    bg.setFillColor(sf::Color::Black);

    // Set load text
    text.setFont(getData().getFont(FONT));
    text.setCharacterSize(92);
    text.setColor(sf::Color::White);
    text.setString("Loading");
    text.setOrigin(
        text.getLocalBounds().left,
        text.getLocalBounds().top);

    // Text box
    textBox.x = text.getLocalBounds().width;
    textBox.y = text.getLocalBounds().height;

    // Update sizes of elements
    updateResized();

    // Update other elements
    update();
}

LoadFrame::~LoadFrame()
{
    if (getData().hasImage(BG))
        getData().removeImage(BG);
}

void LoadFrame::updateResized()
{
    bg.setPosition(0, 0);
    bg.setSize(static_cast<sf::Vector2f>(getWindow().getSize()));

    text.setPosition(
        (getWindow().getSize().x - textBox.x) / 2,
        (getWindow().getSize().y - textBox.y) / 2);
}

void LoadFrame::update()
{
    clock.restart();

    if (!bgLoaded && getData().hasImage(BG))
    {
        bgTexture.loadFromImage(getData().getImage(BG));
        bg.setTexture(&bgTexture);
        bg.setFillColor(sf::Color::White);

        bgLoaded = true;
    }

    std::string str = "Loading";
    countOfDots = (countOfDots + 1) % 4;
    for (int i = 0; i < countOfDots; i++)
        str.push_back('.');
    text.setString(str);
}

void LoadFrame::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::Resized)
        updateResized();
}

void LoadFrame::draw()
{
    sf::Time time = clock.getElapsedTime();
    sf::Int32 ms = time.asMilliseconds();

    if (ms >= DELAY)
        update();

    getWindow().draw(bg);
    getWindow().draw(text);
}

}};
