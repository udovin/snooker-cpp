#pragma once

#include <stdexcept>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace app { namespace data {

class FontManager
{
protected:
    std::map<std::string, sf::Font> fonts;

public:
    FontManager();
    ~FontManager();

    void clearFonts();

    void addFont(const std::string &, const sf::Font &);
    const sf::Font &getFont(const std::string &) const;
    bool hasFont(const std::string &) const;
    void removeFont(const std::string &);
};

}};
