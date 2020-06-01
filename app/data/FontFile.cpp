#include "FontFile.h"

namespace app { namespace data {

FontFile::FontFile(const std::string &filename)
    : sf::Font()
{
    if (!loadFromFile(filename))
        throw std::runtime_error("Failed to load font from file");
}

}};
