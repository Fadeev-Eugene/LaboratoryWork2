#ifndef MOVE_MANAGER_H
#define MOVE_MANAGER_H

#include <unordered_set>


class Animatronic;


class Room;


class MoveManager{
private:
    std::unordered_set<Animatronic*> animatronics;
public:
    void update();
    void addAnimatronic(Animatronic*);
    void transition(Animatronic* animatronic, Room* current_room, Room* new_room);
};

#endif
