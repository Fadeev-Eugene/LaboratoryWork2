#ifndef ANIMATRONIC_H
#define ANIMATRONIC_H

#include <string>

class Room;

class MoveManager;

class Animatronic{
protected:
    std::string name;
    Room* current_room;
    unsigned int max_cooldown;
    unsigned int remaining_cooldown;
public:
    Animatronic(const std::string& name, Room* start_room, int cooldown); 
    std::string getName(){return name;}
    Room* where(){return current_room;}
    void update(MoveManager* mm);
    virtual void move(MoveManager* mm);
    virtual Room* ai();
    virtual ~Animatronic() = default;
};

#endif
