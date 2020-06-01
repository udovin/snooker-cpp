#include "Frame.h"

namespace app { namespace frames {

Frame::Frame(Application &application)
    : application(application)
{}

Frame::~Frame()
{}

Application &Frame::getApplication()
{
    return application;
}

sf::RenderWindow &Frame::getWindow()
{
    return getApplication().getWindow();
}

data::DataManager &Frame::getData()
{
    return getApplication().getData();
}

void Frame::handleEvent(sf::Event &event)
{}

void Frame::draw()
{}

}};
