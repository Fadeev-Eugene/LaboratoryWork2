#include "Animatronic.h"
#include "Room.h"
#include "MoveManager.h"
#include <vector>
#include <random>


Animatronic::Animatronic(const std::string& animatronicName, Room* start_room, int cooldown): name(animatronicName), current_room(start_room), max_cooldown(cooldown), remaining_cooldown(cooldown){}

void Animatronic::update(MoveManager* mm){
    if (remaining_cooldown == 0){
        move(mm);
    }
    else{
        remaining_cooldown--;
    }
}

void Animatronic::move(MoveManager* mm){
    Room* next_room = ai();
    
    mm->transition(this, where(), next_room);
    
    current_room = next_room;
    
    remaining_cooldown = max_cooldown;
}


Room* Animatronic::ai(){
    std::unordered_set<Room*> rooms = current_room->getConnectedRooms();
    std::vector<Room*> vec(rooms.begin(), rooms.end());
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, vec.size() - 1);
    
    return vec[dist(gen)]; 
}


