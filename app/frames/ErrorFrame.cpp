#include "ErrorFrame.h"

namespace app { namespace frames {

const std::string ErrorFrame::FONT = "nautilus";

ErrorFrame::ErrorFrame(Application &application)
    : Frame(application), title(), description()
    , font(getData().getFont(FONT))
{
    // Clear all data
    getData().clearFonts();
    getData().clearImages();
    getData().clearSounds();

    title.setCharacterSize(76);
    title.setFont(font);
    title.setColor(sf::Color::White);
    title.setString("Runtime error");
    title.setPosition(100, 40);
    description.setCharacterSize(32);
    description.setFont(font);
    description.setColor(sf::Color::White);
    description.setString(
        "We're sorry, but there was a critical error.\n"
        "Possibly some data are corrupted.\n"
        "In any case, try to restart the application."
    );
    description.setPosition(100, 150);
}

void ErrorFrame::handleEvent(sf::Event &event)
{}

void ErrorFrame::draw()
{
    getWindow().draw(title);
    getWindow().draw(description);
}

}};
