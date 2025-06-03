#ifndef CORE_H
#define CORE_H

#include "Room.h"
#include "RoomManager.h"
#include "AnimatronicManager.h"
#include "MoveManager.h"
#include "Player.h"
#include "FrameManager.h"
#include "DBworker.h"
#include "Core.h"

class Core{
private:
    MoveManager* mm;
    RoomManager* rm;
    Room* left;
    Room* right;
    Room* currentRoom;
    Player* p;
    FrameManager* fm;
    bool isRunning;
    int tickCount;
    bool cheat;
    DBworker dbworker;
    
    void cheatOutput();   
    void leftDoorOutput();
    void rightDoorOutput(); 
    void camOutput();

public:
    Core(MoveManager* mm, RoomManager* rm, Player* p, FrameManager* fm);
    void run();
    void stop();
    void handleInput(char key);
    bool getStatus(){return isRunning;}
    void death();
    void update();
    sf::Texture* getCurrentFrame();
};

#endif
