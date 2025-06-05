#ifndef FREDDY_H
#define FREDDY_H

#include "Animatronic.h"
#include <vector>


class Freddy: public Animatronic{
private:
    std::vector<std::string> valid_rooms = {"1B", "7", "6", "4B", "4A", "right", "Security Room"};
public:
    Freddy(const std::string& animatronicName, Room* start_room, int cooldown): Animatronic(animatronicName, start_room, cooldown){};

    Room* ai() override; 
};


#endif
