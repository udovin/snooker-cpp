#pragma once

#include "FontManager.h"
#include "ImageManager.h"
#include "SoundManager.h"

namespace app { namespace data {

class DataManager
    : public FontManager, public ImageManager, public SoundManager
{
public:
    DataManager();
    ~DataManager();
};

}};
