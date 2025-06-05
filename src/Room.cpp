#include "Room.h"


Room::Room(const std::string& roomName): name(roomName) {}

void Room::addAnimatronic(Animatronic* anim){
    if (animatronics.count(anim) == 0){
        animatronics.insert(anim);
    } 
}

void Room::removeAnimatronic(Animatronic* anim){
    if (animatronics.count(anim) != 0){
        animatronics.erase(anim);
    } 
}

std::unordered_set<Animatronic*> Room::getAnimatronics(){
    return animatronics;
}
    
void Room::addRoom(Room* room){
    if (connectedRooms.count(room) == 0){
        connectedRooms.insert(room);
    }
}

void Room::removeRoom(Room* room){
    if (connectedRooms.count(room) != 0){
        connectedRooms.erase(room);
    }
}

std::unordered_set<Room*> Room::getConnectedRooms(){
    return connectedRooms;
}
