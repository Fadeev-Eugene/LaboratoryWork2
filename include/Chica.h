#ifndef CHICA_H
#define CHICA_H

#include "Animatronic.h"
#include <vector>

class Chica: public Animatronic{
private:
    std::vector<std::string> valid_rooms = {"1B", "7", "6", "4B", "4A", "right", "Security Room"};
public:
    Chica(const std::string& animatronicName, Room* start_room, int cooldown): Animatronic(animatronicName, start_room, cooldown){};

    Room* ai() override; 
};

#endif
