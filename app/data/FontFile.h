#pragma once

#include <string>
#include <stdexcept>
#include <SFML/Graphics.hpp>

namespace app { namespace data {

class FontFile : public sf::Font
{
public:
    FontFile(const std::string &);
};

}};
