#include "SoundManager.h"

namespace app { namespace data {

SoundManager::SoundManager()
    : sounds()
{}

SoundManager::~SoundManager()
{
    clearSounds();
}

void SoundManager::clearSounds()
{
    sounds.clear();
}

void SoundManager::addSound(const std::string &name, const sf::SoundBuffer &sound)
{
    bool status = sounds.insert(make_pair(name, sound)).second;

    if (!status)
        throw std::runtime_error("Sound already exists");
}

const sf::SoundBuffer &SoundManager::getSound(const std::string &name) const
{
    std::map<std::string, sf::SoundBuffer>::const_iterator it;

    it = sounds.find(name);

    if (it == sounds.end())
        throw std::runtime_error("Sound does not exist");

    return it->second;
}

bool SoundManager::hasSound(const std::string &name) const
{
    return sounds.find(name) != sounds.end();
}

void SoundManager::removeSound(const std::string &name)
{
    std::map<std::string, sf::SoundBuffer>::iterator it;

    it = sounds.find(name);

    if (it == sounds.end())
        throw std::runtime_error("Sound does not exist");

    sounds.erase(it);
}

}};
