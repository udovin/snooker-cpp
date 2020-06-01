#pragma once

#include <string>
#include <stdexcept>
#include <SFML/Audio.hpp>

namespace app { namespace data {

class SoundFile : public sf::SoundBuffer
{
public:
    SoundFile(const std::string &);
};

}};
