#include "MoveManager.h"
#include "Animatronic.h"
#include "Room.h"

#include <unordered_set>

void MoveManager::addAnimatronic(Animatronic* animatronic){
    animatronics.insert(animatronic);
}


void MoveManager::update(){
    for (Animatronic* animatronic: animatronics){
        animatronic->update(this);
    }
}

void MoveManager::transition(Animatronic* animatronic, Room* current_room, Room* new_room){
    current_room->removeAnimatronic(animatronic);
    new_room->addAnimatronic(animatronic);
}


