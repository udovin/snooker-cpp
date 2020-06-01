#include "FontResource.h"

namespace app { namespace data {

FontResource::FontResource(const std::string &resname)
    : sf::Font()
{
    HRSRC rsrcData = FindResource(NULL, resname.c_str(), RT_RCDATA);
    if (!rsrcData)
        throw std::runtime_error("Failed to find resource");

    DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
    if (rsrcDataSize <= 0)
        throw std::runtime_error("Size of resource is zero");

    HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
    if (!grsrcData)
        throw std::runtime_error("Failed to load resource");

    LPVOID firstByte = LockResource(grsrcData);
    if (!firstByte)
        throw std::runtime_error("Failed to lock resource");

    if (!loadFromMemory(firstByte, rsrcDataSize))
        throw std::runtime_error("Failed to load font from memory");
}

}};
