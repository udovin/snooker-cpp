#include "ImageFile.h"

namespace app { namespace data {

ImageFile::ImageFile(const std::string &filename)
    : sf::Image()
{
    if (!loadFromFile(filename))
        throw std::runtime_error("Failed to load image from file");
}

}};
