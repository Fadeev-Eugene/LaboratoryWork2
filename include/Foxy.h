#ifndef FOXY_H
#define FOXY_H

#include "Animatronic.h"
#include <vector>

class Foxy: public Animatronic{
private:
    std::vector<std::string> foxy_path = {"1C", "2A", "2B", "left", "Security Room"};
    Room* start_room;
public:
    Foxy(const std::string& animatronicName, Room* start_room, int cooldown): Animatronic(animatronicName, start_room, cooldown), start_room(start_room){};
    void move(MoveManager* mm) override;
    Room* ai() override; 
};

#endif
