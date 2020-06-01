#pragma once

#include <stdexcept>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace app { namespace data {

class ImageManager
{
protected:
    std::map<std::string, sf::Image> images;

public:
    ImageManager();
    ~ImageManager();

    void clearImages();

    void addImage(const std::string &, const sf::Image &);
    const sf::Image &getImage(const std::string &) const;
    bool hasImage(const std::string &) const;
    void removeImage(const std::string &);
};

}};
