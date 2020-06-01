#pragma once

#include <string>
#include <stdexcept>
#include <SFML/Graphics.hpp>

// Windows Only
#include <windows.h>

namespace app { namespace data {

class FontResource : public sf::Font
{
public:
    FontResource(const std::string &);
};

}};
