#include "RoomManager.h"
#include "Room.h"
#include "SecurityRoom.h"
#include <string>
#include <unordered_set>


RoomManager::RoomManager(){
    Room* r_1A = new Room("1A");
    Room* r_1B = new Room("1B"); 
    Room* r_1C = new Room("1C"); 
    Room* r_2A = new Room("2A"); 
    Room* r_2B = new Room("2B"); 
    Room* r_3 = new Room("3"); 
    Room* r_4A = new Room("4A"); 
    Room* r_4B = new Room("4B"); 
    Room* r_5 = new Room("5"); 
    Room* r_6= new Room("6"); 
    Room* r_7 = new Room("7"); // FNAF 1 map
    
    addConnection(r_1A, r_1B);
    addConnection(r_5, r_1B);
    addConnection(r_7, r_1B);
    addConnection(r_1C, r_2A);
    addConnection(r_6, r_1B);
    addConnection(r_2A, r_1B);
    addConnection(r_4A, r_1B);
    
    addConnection(r_4A, r_4B);
    addConnection(r_2A, r_2B);
    addConnection(r_2A, r_3);
    
    all_rooms.insert(r_1A);
    all_rooms.insert(r_1B);
    all_rooms.insert(r_1C);
    all_rooms.insert(r_2A);
    all_rooms.insert(r_2B);
    all_rooms.insert(r_3);
    all_rooms.insert(r_4A);
    all_rooms.insert(r_4B);
    all_rooms.insert(r_5);
    all_rooms.insert(r_6);
    all_rooms.insert(r_7);

    Room* left = new Room("left");
    Room* right = new Room("right"); // Places near doors
    addConnection(left, r_2B);
    addConnection(right, r_4B);
    
    all_rooms.insert(left);
    all_rooms.insert(right);
    
    Room* sr = new SecurityRoom("Security Room", left, right, this); // Security room
    addConnection(left, sr);
    addConnection(right, sr);
    all_rooms.insert(sr);
}


void RoomManager::addConnection(Room* r1, Room* r2){
    r1->addRoom(r2);
    r2->addRoom(r1);
}

void RoomManager::removeConnection(Room* r1, Room* r2){
    r1->removeRoom(r2);
    r2->removeRoom(r1);
}


Room* RoomManager::getRoom(std::string name){
    for (Room* room : all_rooms){
        if (room->getName() == name){
            return room;
        } 
    }
    static Room nullroom("nullroom");
    return &nullroom;
}


RoomManager::~RoomManager(){
    for (Room* room : all_rooms){
        delete room;
    }
}
