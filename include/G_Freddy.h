#ifndef G_FREDDY_H
#define G_FREDDY_H

#include "Animatronic.h"
#include <vector>


class G_Freddy: public Animatronic{
public:
    G_Freddy(const std::string& animatronicName, Room* start_room, int cooldown): Animatronic(animatronicName, start_room, cooldown){};

    Room* ai() override; 
};


#endif
