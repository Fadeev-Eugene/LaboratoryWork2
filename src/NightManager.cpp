#include "NightManager.h"
#include <iostream>
#include "Core.h"
#include "Room.h"
#include "Animatronic.h"
#include "MoveManager.h"
#include <iostream>
#include <string>
#include "DBworker.h"
#include "RoomManager.h"
#include "AnimatronicManager.h"
#include "MoveManager.h"
#include "Door.h"
#include "Player.h"
#include <thread>
#include "SecurityRoom.h"
#include "KeyReader.h"
#include <limits>

NightManager::NightManager(){
    std::cout << R"( ________  ____  _____       _       ________                   
|_   __  ||_   \|_   _|     / \     |_   __  |  .-.      .-.    
  | |_ \_|  |   \ | |      / _ \      | |_ \_|__| |__  __| |__  
  |  _|     | |\ \| |     / ___ \     |  _|  |__   __||__   __| 
 _| |_     _| |_\   |_  _/ /   \ \_  _| |_      | |      | |    
|_____|   |_____|\____||____| |____||_____|     '-'      '-'    
                                                                )" << std::endl;
    int night = nightSelector();
    play(night);
}


int NightManager::nightSelector(){
    int night;
    while (true) {
        std::cout << "Please, select night (1-5) and type it" << std::endl;
        std::cin >> night;
        if (std::cin.fail()) { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please enter a number." << std::endl;
        } else if (night >= 1 && night <= 5) { 
            return night;
        }
    }
}


void NightManager::play(int night){
    RoomManager rm;
    MoveManager mm;
    AnimatronicManager am(&mm, &rm, night);
    
    Player player(&rm);
    
    Core core(&mm, &rm, &player);

    KeyReader kr;

    std::thread core_thread([&]() { core.run(); });

    while (core.getStatus()) {
        char key;
        key = kr.readKey();
        if (key) {
            core.handleInput(key);
        }   
    }
    core_thread.join();
}
