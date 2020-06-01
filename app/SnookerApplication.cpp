#include "SnookerApplication.h"

namespace app {

const _AssetsFile SnookerApplication::ASSETS_FILES[] = {
    (_AssetsFile){_AssetsFile::IMAGE, "loading_bg", "assets/images/loading_bg.png"},
    (_AssetsFile){_AssetsFile::FONT , "consolas"  , "assets/fonts/consolas.ttf"   },
    (_AssetsFile){_AssetsFile::FONT , "helvetica" , "assets/fonts/helvetica.ttf"  },
    (_AssetsFile){_AssetsFile::IMAGE, "info_bar"  , "assets/images/info_bar.png"  },
    (_AssetsFile){_AssetsFile::IMAGE, "table_bg"  , "assets/images/table_bg.png"  },
    (_AssetsFile){_AssetsFile::IMAGE, "ball"      , "assets/images/ball.png"      },
    (_AssetsFile){_AssetsFile::IMAGE, "player"    , "assets/images/player.png"    },
    (_AssetsFile){_AssetsFile::IMAGE, "referee"   , "assets/images/referee.png"   },
    (_AssetsFile){_AssetsFile::SOUND, "kick"      , "assets/sounds/kick.wav"      },
    (_AssetsFile){_AssetsFile::IMAGE, "game_bg"   , "assets/images/game_bg.jpg"   },
    (_AssetsFile){_AssetsFile::IMAGE, "cue"       , "assets/images/cue.png"       },
    (_AssetsFile){_AssetsFile::IMAGE, "menu_bg"   , "assets/images/menu_bg.png"   },
    (_AssetsFile){_AssetsFile::IMAGE, "button_bg" , "assets/images/button_bg.png" },
    (_AssetsFile){_AssetsFile::IMAGE, "logo"      , "assets/images/logo.png"      },
    (_AssetsFile){_AssetsFile::SOUND, "music_1"   , "assets/sounds/music_1.ogg"   }
};

SnookerApplication::SnookerApplication(sf::RenderWindow &window)
    : Application(window), drawFrame(0)
    , loadDynamicAssetsTh(loadDynamicAssets, this)
    , wantToggleFrame(T_NONE)
{
    // Load static assets
    loadStaticAssets();

    // Toggle to load frame
    toggleLoadFrame();

    // Load dynamic assets
    loadDynamicAssetsTh.launch();
}

SnookerApplication::~SnookerApplication()
{
    // Delete frame
    delete drawFrame;

    // Terminate load dynamic assets
    loadDynamicAssetsTh.terminate();
}

void SnookerApplication::handleEvent(sf::Event &event)
{
    try
    {
        // Lock draw mutex
        sf::Lock lock(drawMutex);

        // Close window
        if (event.type == sf::Event::Closed)
            getWindow().close();

        // Resize support
        if (event.type == sf::Event::Resized)
            getWindow().setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));

        // Handle event
        if (drawFrame != 0)
            drawFrame->handleEvent(event);
    }
    catch (const std::exception &e)
    {
        // Show error
        std::cerr << "Error: " << e.what() << std::endl;

        // Show error frame
        toggleErrorFrame();
    }
}

void SnookerApplication::drawWindow()
{
    try
    {
        if (wantToggleFrame != T_NONE)
        {
            if (wantToggleFrame == T_GAME_FRAME)
                toggleGameFrame();

            if (wantToggleFrame == T_MENU_FRAME)
                toggleMenuFrame();

            wantToggleFrame = T_NONE;
        }

        // Lock draw mutex
        sf::Lock lock(drawMutex);

        // Start drawing
        getWindow().clear(sf::Color::Black);

        // Draw frame
        if (drawFrame != 0)
            drawFrame->draw();

        // Render window
        getWindow().display();
    }
    catch (const std::exception &e)
    {
        // Show error
        std::cerr << "Error: " << e.what() << std::endl;

        // Show error frame
        toggleErrorFrame();
    }
}

void SnookerApplication::loadStaticAssets()
{
    try
    {
        {
            std::cerr << std::left << std::setw(15) << "Loading font:";
            std::cerr << "resource:font_nautilus" << std::endl << "... ";
            data::FontResource font("font_nautilus");
            getData().addFont("nautilus", font);
            std::cerr << "Font loaded." << std::endl;
        }

        std::cerr << "All static assets loaded." << std::endl;
    }
    catch (const std::exception &e)
    {
        // Show error
        std::cerr << "Error: " << e.what() << std::endl;

        // Close window
        sf::Lock lock(drawMutex);
        getWindow().close();
    }
}

void SnookerApplication::loadDynamicAssets()
{
    try
    {
        int size = sizeof(ASSETS_FILES) / sizeof(ASSETS_FILES[0]);

        for (int i = 0; i < size; i++)
        {
            switch(ASSETS_FILES[i].type)
            {
                case _AssetsFile::FONT:
                {
                    std::cerr << std::left << std::setw(15) << "Loading font:";
                    std::cerr << ASSETS_FILES[i].path << std::endl << "... ";
                    data::FontFile font(ASSETS_FILES[i].path);
                    sf::Lock lock(drawMutex);
                    getData().addFont(ASSETS_FILES[i].name, font);
                    std::cerr << "Font loaded." << std::endl;
                    break;
                }
                case _AssetsFile::IMAGE:
                {
                    std::cerr << std::left << std::setw(15) << "Loading image:";
                    std::cerr << ASSETS_FILES[i].path << std::endl << "... ";
                    data::ImageFile image(ASSETS_FILES[i].path);
                    sf::Lock lock(drawMutex);
                    getData().addImage(ASSETS_FILES[i].name, image);
                    std::cerr << "Image loaded." << std::endl;
                    break;
                }
                case _AssetsFile::SOUND:
                {
                    std::cerr << std::left << std::setw(15) << "Loading sound:";
                    std::cerr << ASSETS_FILES[i].path << std::endl << "... ";
                    data::SoundFile sound(ASSETS_FILES[i].path);
                    sf::Lock lock(drawMutex);
                    getData().addSound(ASSETS_FILES[i].name, sound);
                    std::cerr << "Sound loaded." << std::endl;
                    break;
                }
            }
        }

        std::cerr << "All dynamic assets loaded." << std::endl;

        // Toggle to Menu Frame
        toggleMenuFrame();
        /*// Toggle to Game Frame
        toggleGameFrame();*/
    }
    catch (const std::exception &e)
    {
        // Show error
        std::cerr << "Error: " << e.what() << std::endl;

        // Show error frame
        toggleErrorFrame();
    }
}

void SnookerApplication::toggleLoadFrame()
{
    sf::Lock lock(drawMutex);
    delete drawFrame;
    drawFrame = new frames::LoadFrame(*this);
}

void SnookerApplication::toggleGameFrame()
{
    sf::Lock lock(drawMutex);
    delete drawFrame;
    drawFrame = new frames::GameFrame(*this);
}

void SnookerApplication::toggleMenuFrame()
{
    sf::Lock lock(drawMutex);
    delete drawFrame;
    drawFrame = new frames::MenuFrame(*this);
}

void SnookerApplication::toggleErrorFrame()
{
    sf::Lock lock(drawMutex);
    delete drawFrame;
    drawFrame = new frames::ErrorFrame(*this);
}

void SnookerApplication::wantToggleGameFrame()
{
    wantToggleFrame = T_GAME_FRAME;
}

void SnookerApplication::wantToggleMenuFrame()
{
    wantToggleFrame = T_MENU_FRAME;
}

};
