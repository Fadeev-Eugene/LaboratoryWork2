#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_set>
#include "Room.h"
#include "Animatronic.h"
#include "DBworker.h"

class FrameManager{
private:
    std::map<std::string, sf::Texture> framebase;
    Room* currentRoom;
    std::unordered_set<Animatronic*> status;
    DBworker* dbworker;
    sf::Texture* currentFrame;

public:
    FrameManager(Room* room, DBworker* dbworker);
    std::vector<std::string> getFilesInDirectory(const std::string& directory);
    sf::Texture* getCurrentFrame();
    void update();
    void updateRoom(Room* room);
    sf::Texture* getFrame(){return currentFrame;}
};

#endif
