#pragma once

#include <stdexcept>
#include <map>
#include <string>
#include <SFML/Audio.hpp>

namespace app { namespace data {

class SoundManager
{
protected:
    std::map<std::string, sf::SoundBuffer> sounds;

public:
    SoundManager();
    ~SoundManager();

    void clearSounds();

    void addSound(const std::string &, const sf::SoundBuffer &);
    const sf::SoundBuffer &getSound(const std::string &) const;
    bool hasSound(const std::string &) const;
    void removeSound(const std::string &);
};

}};
