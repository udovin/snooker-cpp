#include "ImageManager.h"

namespace app { namespace data {

ImageManager::ImageManager()
    : images()
{}

ImageManager::~ImageManager()
{
    clearImages();
}

void ImageManager::clearImages()
{
    images.clear();
}

void ImageManager::addImage(const std::string &name, const sf::Image &image)
{
    bool status = images.insert(make_pair(name, image)).second;

    if (!status)
        throw std::runtime_error("Image already exists");
}

const sf::Image &ImageManager::getImage(const std::string &name) const
{
    std::map<std::string, sf::Image>::const_iterator it;

    it = images.find(name);

    if (it == images.end())
        throw std::runtime_error("Image does not exist");

    return it->second;
}

bool ImageManager::hasImage(const std::string &name) const
{
    return images.find(name) != images.end();
}

void ImageManager::removeImage(const std::string &name)
{
    std::map<std::string, sf::Image>::iterator it;

    it = images.find(name);

    if (it == images.end())
        throw std::runtime_error("Image does not exist");

    images.erase(it);
}

}};
