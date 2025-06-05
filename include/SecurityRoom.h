#ifndef SECURITY_ROOM
#define SECURITY_ROOM

#include <unordered_set>
#include "RoomManager.h"
#include "Room.h"
#include "Door.h"

class SecurityRoom: public Room{
private:
    Door* leftDoor;
    Door* rightDoor;
public:
    SecurityRoom(const std::string& roomName, Room* left, Room* right, RoomManager* rm): Room(roomName){
        leftDoor = new Door(rm, this, left);
        rightDoor = new Door(rm, this, right);
    }
    void closeLeftDoor(){leftDoor->close();} 
    void openLeftDoor(){leftDoor->open();}
    void closeRightDoor(){rightDoor->close();}
    void openRightDoor(){rightDoor->open();}
    ~SecurityRoom(){delete leftDoor; delete rightDoor;}
};

#endif
