#ifndef ROOM_H
#define ROOM_H


#include <unordered_set>
#include <string>
#include "Animatronic.h"


class Room {
protected:
    std::string name;
    std::unordered_set<Room*> connectedRooms;  
    std::unordered_set<Animatronic*> animatronics;  

public:
    Room(const std::string& roomName);
    virtual ~Room() = default;
    std::string getName(){return name;}
    
    void addAnimatronic(Animatronic* anim);
    void removeAnimatronic(Animatronic* anim);
    std::unordered_set<Animatronic*> getAnimatronics();
    
    void addRoom(Room* room);
    void removeRoom(Room* room);
    std::unordered_set<Room*> getConnectedRooms();
};

#endif 
