#ifndef ANIMATRONIC_MANAGER_H
#define ANIMATRONIC_MANAGER_H

#include <unordered_set>
#include <string>


class Animatronic;

class MoveManager;

class RoomManager;

class DBworker;

class Room;

class AnimatronicManager{
private:
    std::unordered_set<Animatronic*> all_animatronics;
    MoveManager* mm;
    RoomManager* rm;
    int night;
    DBworker* dbworker;

public:
    AnimatronicManager(MoveManager* mm, RoomManager* rm,  int night);
    
    void createAnimatronic(std::string name);

    std::unordered_set<Animatronic*> getAllAnimatronics(){return all_animatronics;}

    ~AnimatronicManager();
};

#endif
