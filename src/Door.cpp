#include "Door.h"
#include "RoomManager.h"
#include "Room.h"

Door::Door(RoomManager* rm, Room* first, Room* second): rm(rm), first(first), second(second) {}


void Door::open(){
    std::unordered_set<Room*> rooms = first->getConnectedRooms();
    if (rooms.find(second) == rooms.end()) {
        rm->addConnection(first, second);
    }
}

void Door::close(){
    std::unordered_set<Room*> rooms = first->getConnectedRooms();
    if (rooms.find(second) != rooms.end()) {
        rm->removeConnection(first, second);
    }
}
