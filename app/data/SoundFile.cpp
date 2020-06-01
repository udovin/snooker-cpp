#include "SoundFile.h"

namespace app { namespace data {

SoundFile::SoundFile(const std::string &filename)
    : sf::SoundBuffer()
{
    if (!loadFromFile(filename))
        throw std::runtime_error("Failed to load sound from file");
}

}};
