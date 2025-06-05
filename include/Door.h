#ifndef DOOR_H
#define DOOR_H

#include <string>

class Room;

class RoomManager;

class Door{
private: 
    RoomManager* rm;
    Room* first;
    Room* second;    
public:
    Door(RoomManager* rm, Room* first, Room* second); 
    void open();
    void close();
};

#endif
