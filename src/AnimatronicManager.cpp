#include "AnimatronicManager.h"
#include "Animatronic.h"
#include "MoveManager.h"
#include "RoomManager.h"
#include "DBworker.h"
#include "Room.h"
#include <unordered_set>
#include <string>
#include "Bonnie.h"
#include "Foxy.h"
#include "Chica.h"
#include "Freddy.h"
#include "G_Freddy.h"


AnimatronicManager::AnimatronicManager(MoveManager* mm, RoomManager* rm,  int night) : mm(mm), rm(rm), night(night), dbworker(new DBworker("Nights.db")){
    std::unordered_set<std::string> names{"Freddy Fazbear", "Bonnie", "Chica", "Foxy", "Golden Freddy"};
    for (std::string name : names){
        createAnimatronic(name);
    }
}

void AnimatronicManager::createAnimatronic(std::string name){
    std::string start_room_name = dbworker->getAnimatronicStartRoom(name, night);
    int activity = dbworker->getAnimatronicActivity(name, night);
    Animatronic* anim;

    Room* startRoom = rm->getRoom(start_room_name);
    if (startRoom != nullptr) {
        if (name == "Bonnie"){
            anim = new Bonnie(name, startRoom, activity);

        } else if (name == "Freddy Fazbear") {
            anim = new Freddy(name, startRoom, activity);

        } else if (name == "Chica") {
            anim = new Chica(name, startRoom, activity);

        } else if (name == "Foxy") {
            anim = new Foxy(name, startRoom, activity);

        } else if (name == "Golden Freddy") {
            anim = new G_Freddy(name, startRoom, activity);

        } else {
            anim = new Animatronic(name, startRoom, activity);
        }     
        all_animatronics.insert(anim);
        mm->addAnimatronic(anim);
        startRoom->addAnimatronic(anim);
    } else {
        std::cerr << "Error: Room " << start_room_name << " not found!" << std::endl;
    }  
}


AnimatronicManager::~AnimatronicManager(){
    for (Animatronic* anim : all_animatronics){
        delete anim;
    }
    delete dbworker;
}
