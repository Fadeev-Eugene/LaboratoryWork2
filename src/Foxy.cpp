#include "Foxy.h"
#include "Animatronic.h"
#include "Room.h"
#include "MoveManager.h"
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>


void Foxy::move(MoveManager* mm){
    Room* next_room = ai();
    
    mm->transition(this, where(), next_room);
    
    current_room = next_room;
}


Room* Foxy::ai() {
    std::unordered_set<Room*> rooms = current_room->getConnectedRooms();
    std::string current_name = current_room->getName();

    auto it = std::find(foxy_path.begin(), foxy_path.end(), current_name);
    
    if (it != foxy_path.end() && std::next(it) != foxy_path.end()) {
        std::string next_room_name = *std::next(it);         
        for (Room* room : rooms) {
            if (room->getName() == next_room_name) {
                remaining_cooldown = 120;
                return room; 
            }            
        }
        remaining_cooldown = max_cooldown;
        return start_room;
    }
    return current_room;
}
