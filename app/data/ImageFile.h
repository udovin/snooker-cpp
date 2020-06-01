#pragma once

#include <string>
#include <stdexcept>
#include <SFML/Graphics.hpp>

namespace app { namespace data {

class ImageFile : public sf::Image
{
public:
    ImageFile(const std::string &);
};

}};
