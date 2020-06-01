#pragma once

#include "Application.h"
#include "data/all.h"
#include "frames/all.h"

#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>

namespace app {

struct _AssetsFile
{
    enum Type
    {
        FONT,
        IMAGE,
        SOUND
    };

    Type type;
    std::string name, path;
};

class SnookerApplication : public Application
{
private:
    static const _AssetsFile ASSETS_FILES[];

    enum ToggleFrame
    {
        T_NONE,
        T_MENU_FRAME,
        T_GAME_FRAME
    };

    // Draw mutex
    sf::Mutex drawMutex;

    // Current frame
    frames::Frame *drawFrame;
    ToggleFrame wantToggleFrame;

    // Thread for loading dynamic assets
    sf::Thread loadDynamicAssetsTh;

public:
    SnookerApplication(sf::RenderWindow &);
    virtual ~SnookerApplication();

    virtual void handleEvent(sf::Event &);
    virtual void drawWindow();

private:
    void loadStaticAssets();
    void loadDynamicAssets();

    void toggleLoadFrame();
    void toggleGameFrame();
    void toggleMenuFrame();
    void toggleErrorFrame();

public:
    void wantToggleGameFrame();
    void wantToggleMenuFrame();
};

};
