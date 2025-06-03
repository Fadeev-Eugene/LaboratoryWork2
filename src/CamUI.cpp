#include "CamUI.h"
#include "Core.h"
CamUI::CamUI(sf::Texture* new_frame, Core* core) 
    : window(sf::VideoMode(854, 480), "Camera System"), 
      frame(new_frame), 
      isRunning(true), core(core)
{
    if (!window.isOpen()) {
        throw std::runtime_error("Failed to create window!");
    }
    window.setFramerateLimit(60);
    initMinimap();
}

CamUI::~CamUI() {
    if (window.isOpen()) {
        window.close();
    }
}

void CamUI::updateFrame(sf::Texture* new_frame) {
    frame = new_frame;
}

void CamUI::update() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
            window.close();
        }
    }
    sf::Sprite sprite(*frame);
    window.clear();
    window.draw(sprite);
    window.draw(minimapSprite);
    window.display();
}

void CamUI::run(){
    while ((window.isOpen()) and (core->getStatus())){
        update();
        core->update();
        auto new_frame = core->getCurrentFrame();
        if (new_frame != frame){
            updateFrame(new_frame);
        }
    }
}

bool CamUI::isOpen() const {
    return isRunning && window.isOpen();
}

void CamUI::initMinimap() {
    if (!minimapTexture.loadFromFile("img/map.png")) {
        std::cerr << "Failed to load minimap texture!" << std::endl;
        return;
    }
    
    minimapSprite.setTexture(minimapTexture);
    
    float scale = 0.3f;
    minimapSprite.setScale(scale, scale);
    
    sf::Vector2f position(
        window.getSize().x - minimapSprite.getGlobalBounds().width - 10,
        window.getSize().y - minimapSprite.getGlobalBounds().height - 10 
    );
    
    minimapSprite.setPosition(position);
}
