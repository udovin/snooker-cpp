#include "FrameRate.h"

namespace app { namespace gui {

const int FrameRate::DELAY = 500;

FrameRate::FrameRate()
    : sf::Text(), clock(), frames(0)
{
    setString("Frame rate: ---");
}

FrameRate::FrameRate(const sf::Font &font, unsigned int size)
    : sf::Text(), clock(), frames(0)
{
    setString("Frame rate: ---");
    setFont(font);
    setCharacterSize(size);
}

void FrameRate::update()
{
    frames++;

    sf::Time time = clock.getElapsedTime();
    sf::Int32 ms = time.asMilliseconds();

    if (ms >= DELAY)
    {
        std::stringstream ss;
        ss << std::fixed;
        ss << std::setprecision(2);
        ss << "Frame rate: ";
        ss << float(frames * 1000) / ms;
        setString(ss.str().c_str());
        clock.restart(), frames = 0;
    }
}

}};
