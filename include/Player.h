#ifndef PLAYER_H
#define PLAYER_H

#include "RoomManager.h"
#include "Room.h"
#include "SecurityRoom.h"

class Player {
private:
    bool left_door = true;
    bool right_door = true;
    bool left_light = false;
    bool right_light = false;
    unsigned int energy_lost = 36000;
    bool alive = true;    
    SecurityRoom* sr;    

public:
    Player(RoomManager* rm) : sr(static_cast<SecurityRoom*>(rm->getRoom("Security Room"))){};
    void update();
    void updateDoor(char key);
    void updateLight(char key);
    unsigned int energyCheck() {return energy_lost;}
    bool leftDoorStatus() {return left_door;}    
    bool rightDoorStatus() {return right_door;}
    bool leftLightStatus() {return left_light;}
    bool rightLightStatus() {return right_light;}
    bool isAlive() {return alive;}     
};
#endif 
