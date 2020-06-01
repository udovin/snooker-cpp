#include "FontManager.h"

namespace app { namespace data {

FontManager::FontManager()
    : fonts()
{}

FontManager::~FontManager()
{
    clearFonts();
}

void FontManager::clearFonts()
{
    fonts.clear();
}

void FontManager::addFont(const std::string &name, const sf::Font &font)
{
    bool status = fonts.insert(make_pair(name, font)).second;

    if (!status)
        throw std::runtime_error("Font already exists");
}

const sf::Font &FontManager::getFont(const std::string &name) const
{
    std::map<std::string, sf::Font>::const_iterator it;

    it = fonts.find(name);

    if (it == fonts.end())
        throw std::runtime_error("Font does not exist");

    return it->second;
}

bool FontManager::hasFont(const std::string &name) const
{
    return fonts.find(name) != fonts.end();
}

void FontManager::removeFont(const std::string &name)
{
    std::map<std::string, sf::Font>::iterator it;

    it = fonts.find(name);

    if (it == fonts.end())
        throw std::runtime_error("Font does not exist");

    fonts.erase(it);
}

}};
