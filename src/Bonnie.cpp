#include "Bonnie.h"
#include "Animatronic.h"
#include "Room.h"
#include "MoveManager.h"
#include <vector>
#include <random>
#include <algorithm>

void Bonnie::updateHistory(const std::string& room_name){
    room_history.push_back(room_name);
    if (room_history.size() > history_limit) {
        room_history.erase(room_history.begin());
    }
}

bool Bonnie::wasInRoom(const std::string& room_name){
    return std::find(room_history.begin(), room_history.end(), room_name) != room_history.end();
}

Room* Bonnie::ai() {
    std::unordered_set<Room*> rooms = current_room->getConnectedRooms();
    std::vector<Room*> filtered_rooms;
    
    for (Room* room : rooms){
        if (room->getName() == "Security Room"){
            return room;        
        }
    }


    for (Room* room : rooms) {
        std::string room_name = room->getName();
        if (std::find(valid_rooms.begin(), valid_rooms.end(), room_name) != valid_rooms.end()) {
            if (!wasInRoom(room_name) || rand() % 2 != 0) { 
                filtered_rooms.push_back(room);
            }
        }
    }

    if (filtered_rooms.empty()) {
        return current_room;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, filtered_rooms.size() - 1);

    Room* next_room = filtered_rooms[dist(gen)];
    updateHistory(next_room->getName());

    return next_room;
}
