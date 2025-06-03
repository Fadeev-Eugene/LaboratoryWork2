#ifndef CORE_H
#define CORE_H

#include "Room.h"
#include "RoomManager.h"
#include "AnimatronicManager.h"
#include "MoveManager.h"
#include "Player.h"

class Core{
private:
    MoveManager* mm;
    RoomManager* rm;
    Room* left;
    Room* right;
    Room* currentRoom;
    Player* p;
    bool isRunning;
    int tickCount;
    bool cheat;
    
    void update();
    void cheatOutput();   
    void leftDoorOutput();
    void rightDoorOutput(); 
    void camOutput();

public:
    Core(MoveManager* mm, RoomManager* rm, Player* p);
    void run();
    void stop();
    void handleInput(char key);
    bool getStatus(){return isRunning;}
    void death();
};

#endif
