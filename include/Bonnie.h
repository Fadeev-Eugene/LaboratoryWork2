#ifndef BONNIE_H
#define BONNIE_H

#include "Animatronic.h"
#include <vector>

class Bonnie: public Animatronic{
private:
    std::vector<std::string> room_history;
    const size_t history_limit = 3;
    std::vector<std::string> valid_rooms = {"1B", "2A", "2B", "left", "Security Room"};
public:
    Bonnie(const std::string& animatronicName, Room* start_room, int cooldown): Animatronic(animatronicName, start_room, cooldown){};
    
    void updateHistory(const std::string& room_name);
    
    bool wasInRoom(const std::string& room_name); 

    Room* ai() override; 
};

#endif
