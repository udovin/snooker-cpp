#pragma once

#include <string>
#include <stdexcept>
#include <SFML/Graphics.hpp>

// Windows Only
#include <windows.h>

namespace app { namespace data {

class ImageResource : public sf::Image
{
public:
    ImageResource(const std::string &);
};

}};
