#include "Chica.h"
#include "Animatronic.h"
#include "Room.h"
#include "MoveManager.h"
#include <vector>
#include <random>
#include <algorithm>


Room* Chica::ai() {
    std::unordered_set<Room*> rooms = current_room->getConnectedRooms();
    std::vector<Room*> filtered_rooms;
    
    for (Room* room : rooms){
        if (room->getName() == "Security Room"){
            return room;        
        }
    }

    for (Room* room : rooms) {
        if (std::find(valid_rooms.begin(), valid_rooms.end(), room->getName()) != valid_rooms.end()) {
            filtered_rooms.push_back(room);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, filtered_rooms.size() - 1);

    Room* next_room = filtered_rooms[dist(gen)];

    return next_room;
}
