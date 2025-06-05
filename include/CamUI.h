#ifndef CAMUI_H
#define CAMUI_H

#include <SFML/Graphics.hpp>
#include "Core.h"

class CamUI {
public:
    CamUI(sf::Texture* new_frame, Core* core);
    ~CamUI();
    void updateFrame(sf::Texture* new_frame);
    void update();
    bool isOpen() const;
    void run();    
private:
    sf::RenderWindow window;
    sf::Texture* frame;
    bool isRunning;
    Core* core;

    sf::Texture minimapTexture;
    sf::Sprite minimapSprite;

    void initMinimap();
};

#endif
