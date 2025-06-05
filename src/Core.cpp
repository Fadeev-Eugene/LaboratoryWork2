#include "Core.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>


const std::chrono::milliseconds TICK_DURATION(1000 / 60);

Core::Core(MoveManager* mm, RoomManager* rm, Player* p, FrameManager* fm): mm(mm), rm(rm), left(rm->getRoom("left")), right(rm->getRoom("right")), currentRoom(rm->getRoom("1A")), p(p), fm(fm), isRunning(true), tickCount(0), cheat(false), dbworker("Nights.db"){}

void Core::run() {
    while (isRunning){
        auto start = std::chrono::steady_clock::now();
        update();
        std::this_thread::sleep_until(start + TICK_DURATION);
    }
}

void Core::update() {
    system("clear");
    std::cout << "Time 0" << (tickCount / 2400) << ":" << ((((tickCount % 2400) / 40) < 10) ? "0" : "") << (tickCount % 2400) / 40 << "\n";
    std::cout << "Remaining energy " << p->energyCheck() * 100 / 36000 << "%\n";
    std::cout << "Left door status " << (p->leftDoorStatus() ? "Open" : "Closed") << "\n";
    std::cout << "Right door status " << (p->rightDoorStatus() ? "Open" : "Closed") << "\n";
    tickCount++;
    mm->update();
    p->update();   
    fm->update();
    
    camOutput();

    if (cheat) {
        cheatOutput();
    } else {
        if (p->leftLightStatus()) leftDoorOutput();
        if (p->rightLightStatus()) rightDoorOutput();
    }
    
    if (tickCount > 14400) stop();
    if (!(p->isAlive())) death();
}

void Core::cheatOutput(){
    for (Room* room : rm->getAllRooms()){
        std::cout << room->getName() << " : "; 
        for (Animatronic* anim : room->getAnimatronics()){
            std::cout << "(" << anim->getName() << ") ";        
        }   
        std::cout << dbworker.getCurrentFrame(room);
        std::cout << "\n";
    } 
}

void Core::leftDoorOutput(){
    std::cout << "left" << " : ";
    for (Animatronic* anim : left->getAnimatronics()){
        if (anim->getName() == "Bonnie") std::cout << "(" << anim->getName() << ") ";        
    }   
    std::cout << "\n";
}

void Core::rightDoorOutput(){
    std::cout << "right" << " : ";
    for (Animatronic* anim : right->getAnimatronics()){
        if (anim->getName() == "Chica") std::cout << "(" << anim->getName() << ") ";        
    }   
    std::cout << "\n";
}

void Core::stop() {
    isRunning = false;
    std::cout << R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⠴⠶⠶⠶⢦⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠟⠉⠀⠀⠀⠀⠀⠀⠀⠈⠛⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⢀⣠⠤⠤⠤⣄⣀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⢳⣦⣞⡟⣧⠀⣀⣤⣀⠉⠓⣄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠤⠐⠚⢉⣠⣤⣾⣿⣿⣿⠿⠋⠁⠀⠈⢳⡀⠘⢷⠀⠀⠀⠀
⠀⠀⠀⢀⡴⠶⠦⣼⡧⢤⣤⣀⣀⣀⡤⠴⠶⠶⠶⠒⠚⠉⠉⢀⣀⣹⣯⣉⠀⠀⠀⠀⠀⣿⡟⠀⣼⠀⠀⠀⠀
⠀⠀⣰⠋⠀⠀⣀⣬⠟⢻⡟⠋⠉⠀⠀⠀⠀⢀⣀⣀⡀⠀⢴⣿⣿⣥⣴⣿⣷⡄⠀⠀⣰⠟⠁⣰⡏⠀⠀⠀⠀
⠀⢰⠃⠀⢀⡾⠋⠙⠻⣿⠁⠀⠀⠀⠀⢸⣿⣯⡵⠞⠛⠃⠘⠁⠀⠀⠀⣠⣤⣿⡗⣆⣠⡤⠞⠋⠀⠀⠀⠀⠀
⠀⣿⠀⠀⣼⠃⠀⠀⢀⣿⠀⠀⠀⠀⠀⠈⠛⠁⣀⣀⣀⠀⠀⠀⠀⠀⣸⣿⣿⠿⣟⠻⡅⠀⠀⠀⠀⠀⠀⠀⠀
⠠⣟⠀⠀⣿⠀⠀⠀⢸⠃⠀⠀⠀⠀⠀⣠⣴⣾⣿⠿⠿⣿⣦⠀⠀⢠⣿⣿⡟⢸⣷⣧⢻⣆⠀⠀⠀⠀⠀⠀⠀
⠀⠻⣄⠀⠙⠧⣤⣶⡏⠀⠀⠀⠀⠀⢰⣿⣿⡏⢠⣶⣼⣯⣿⡇⠀⡘⣿⣿⣿⡘⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀
⠀⠀⠈⠉⠛⠛⢻⡿⠃⠀⠀⠀⠀⠀⢸⣿⣿⣇⠈⠻⠟⣀⣿⣧⠾⠛⠛⠿⢿⣿⣿⣿⣽⣿⣿⡆⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢰⠏⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣷⣶⡶⠿⠋⠀⠀⠀⠀⠀⠹⣦⠀⠀⠀⠙⣿⡇⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⣠⠄⠀⠀⠀⠀⠀⠠⣄⡀⠀⠀⠀⣠⣴⣿⠀⠀⢠⣤⣾⡇⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠘⣇⠀⠀⠀⠀⠀⠀⣰⠇⠀⠀⠀⠀⠀⠀⠀⠀⠙⠓⠦⢤⣿⠿⠁⠀⠀⠈⣻⡏⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠙⢧⡀⠀⠀⠀⢀⡏⠀⠀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣦⣄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⣄⠀⠘⢧⡀⠀⠀⠀⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⣻⡿⣿⠇⢸⣷⡄⠀⠀⠀
⠀⠀⠀⢀⣠⡤⠤⠤⠤⠤⣬⣿⡗⠀⠛⠛⠦⢤⣄⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⡴⢟⣭⠞⠃⠚⢶⣈⣷⠀⠀⠀
⠀⢀⡾⣏⠁⠀⠀⠀⠀⠀⠀⠈⠙⠷⣤⣀⡀⠀⠈⠉⠉⠓⣲⡶⠖⣻⣿⣟⣁⣶⡟⠉⠀⠀⠀⠐⣥⣿⠀⠀⠀
⠀⣾⠻⠙⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⢳⣶⡶⠶⠚⣷⠶⠚⠛⠉⠉⠙⣿⠇⠀⠀⠀⠀⢰⣿⠏⠀⠀⠀
⠀⢹⡀⠀⠸⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⢀⣿⣿⠟⢧⡀⠀⠀⢸⣿⡀⣀⣠⣤⡤⠾⠋⠀⠀⠀⠀
⠀⠀⢷⠀⠀⢹⡀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⢸⣁⠀⣿⣿⠏⠀⠀⠙⢦⣀⣼⡟⣿⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠈⢷⣄⠘⣧⠀⠀⠀⢀⣀⣤⠾⠁⠀⢀⡞⠙⣆⣿⢋⡖⠀⠀⠀⠀⠙⣿⡷⠉⠛⠓⠶⠦⣄⡀⠀⠀⠀⠀
⠀⠀⠀⠀⠉⠛⠛⢳⣴⣾⣿⠋⠀⠀⠀⠀⢸⠃⠀⠈⠑⠋⠀⠀⠀⠀⠀⢘⡾⠁⠀⠀⠀⠀⠀⣀⣭⣳⣄⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣼⡏⠁⠀⠀⠀⠀⠀⠀⢻⣄⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⠀⠀⠀⠀⡤⠞⠉⠀⠀⠀⠈⠳⡀
⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⢶⡀⠀⠀⠀⠀⠀⡼⠀⠀⠀⢠⠞⠁⠀⠀⠀⠀⠀⠀⠀⣿
⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⢀⣀⣤⣤⣤⣙⣿⡄⠀⠀⠀⡇⠀⠀⢰⠋⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿
⠀⠀⠀⠀⠀⠀⠀⠀⣧⠀⠀⠀⢀⡴⠚⠃⠀⠀⠀⠀⠀⠙⣿⡓⠛⠛⠷⣄⡀⣼⠀⠀⠀⠀⠀⠀⠀⠀⠠⣼⠃
⠀⠀⠀⠀⠀⠀⠀⠀⢹⡄⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠮⡇⠀⠀⠀⠀⠙⠿⣄⡀⠀⠀⠀⠀⠀⣠⠾⠁⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠸⣷⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡼⠃⠀⠀⠀⠀⠀⠀⠈⠙⠶⠶⢤⡤⠞⠉⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⡇⠀⠀⠀⠀⠀⠀⠀⠀⣠⠜⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠶⣤⣀⡤⠤⠴⠶⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)" << std::endl << "You survived night!" << std::endl;
}

void Core::handleInput(char key) {
    if ((key == '[') or (key == ']')) {
        p->updateDoor(key);
    }
    if ((key == '{') or (key == '}')) {
        p->updateLight(key);    
    }
    if (key == '`'){
        if (cheat) {
            cheat = false;        
        } else {
            cheat = true;     
        }
    }
    if ((key == '0')){
        currentRoom = rm->getRoom("1A");
        fm->updateRoom(rm->getRoom("1A"));
    }   
    if ((key == '1')){
        currentRoom = rm->getRoom("1B");
        fm->updateRoom(rm->getRoom("1B"));
    }
    if ((key == '3')){
        currentRoom = rm->getRoom("5");
        fm->updateRoom(rm->getRoom("5"));
    }
    if ((key == '2')){
        currentRoom = rm->getRoom("1C");
        fm->updateRoom(rm->getRoom("1C"));
    }
    if ((key == '4')){
        currentRoom = rm->getRoom("7");
        fm->updateRoom(rm->getRoom("7"));
    }
    if ((key == '6')){
        currentRoom = rm->getRoom("2A");
        fm->updateRoom(rm->getRoom("2A"));
    }
    if ((key == '7')){
        currentRoom = rm->getRoom("2B");
        fm->updateRoom(rm->getRoom("2B"));
    }
    if ((key == '8')){
        currentRoom = rm->getRoom("4A");
        fm->updateRoom(rm->getRoom("4A"));
    }
    if ((key == '9')){
        currentRoom = rm->getRoom("4B");
        fm->updateRoom(rm->getRoom("4B"));
    }
    if ((key == '5')){
        currentRoom = rm->getRoom("3");
        fm->updateRoom(rm->getRoom("3"));
    }
}

void Core::camOutput(){
    std::cout << currentRoom->getName() << " : "; 
    for (Animatronic* anim : currentRoom->getAnimatronics()){
        std::cout << "(" << anim->getName() << ") ";        
    }   
    std::cout << "\n";
}

void Core::death(){
    isRunning = false;
    std::cout <<R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⢀⣶⣦⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣾⣿⡿⡧⠺⣆⠀⠀⠀⠀⠀⠸⣿⣿⡛⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠹⠟⠑⠙⠁⠰⡀⠻⠀⠀⠀⡀⠀⠀⠀⠠⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣶⡮⣩⣭⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣄⢽⣿⣿⢿⣿⡿⠿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡼⠿⠿⣾⡐⠋⠛⢿⣿⢿⡣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣦⣤⡀⠀⠀⡿⡀⠀⠔⣠⣿⣼⣯⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠙⠿⢁⣴⠀⠀⢀⣵⣯⡻⣿⡟⡹⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠀⠸⠟⡀⣸⢿⠟⠁⠀⠀⢀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢄⠠⠀⠁⠉⠉⠀⠀⠀⡴⢀⡾⢠⣿⣷⡆⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠔⠈⢰⡄⠀⠐⠄⣀⢀⡀⡔⠘⣡⡿⣱⣿⣿⡟⣴⣾⣿⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠌⠀⠀⠀⠙⠦⠀⡀⡘⠈⣁⣤⡦⠫⠺⠿⠿⣿⢐⣴⣵⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣄⠀⠀⠀⠀⠂⠀⠀⠈⠉⠈⠈⠉⠀⠀⠀⠈⢀⣿⡆⠙⢿⣷⣻⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠾⠀⠀⠀⠀⡖⠆⠈⠀⠀⣠⣶⣦⠀⠀⠀⢠⡻⣿⡇⣄⠈⠟⣟⣿⣿⡿⣿⣿⣧⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠢⠏⠀⣀⢠⣾⣿⣿⣻⣷⢤⣤⣼⣿⣜⢧⢿⣇⠀⠙⠛⠋⠋⣩⣽⣦⣤⡀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣞⣛⠀⠀⠀⡂⠐⣸⠿⣷⣮⡻⡿⣿⣯⣿⣽⣗⣽⢿⣿⢸⣿⣿⣧⠀⠀⢀⣶⣿⣿⣿⣿⣧⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⡇⠀⠀⠇⠀⠻⢦⣽⣽⣿⣿⣯⣿⢿⣿⣿⣿⣿⡿⡋⢙⣽⡟⠀⠀⠀⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⡇⠀⠀⠀⠁⣿⣾⣿⣿⣿⣻⣽⣮⣻⣿⣿⣟⣿⢧⣗⢘⣿⠃⠀⠃⠀⢹⣿⣿⣿⣿⡇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣠⣍⠉⠙⣿⡿⠃⠀⠀⠀⠁⢸⣮⣿⣶⣿⣻⣿⣟⣯⣼⣿⣿⣿⣟⣽⠻⠏⢀⣴⣶⠀⢘⣛⣟⣿⠿⠇⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣠⣾⠋⣠⣄⠀⠋⠀⠀⠀⠀⢠⡐⠢⠁⠈⠛⢿⡻⣿⣟⣿⣿⣽⣷⡿⢟⢃⣼⡇⠀⣿⡆⠐⣻⣿⣿⣿⣷⣆⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠚⢿⡿⠁⣁⡉⠀⠀⠀⠀⠀⠀⡀⣙⠂⠘⠀⢀⡀⠈⠁⢉⣉⣉⣥⣤⠾⣃⣾⡿⠳⠀⠟⠎⠸⠍⢛⡛⠛⠻⠿⠀⠀⠀⠀
⠀⠀⠀⠀⠸⠟⠀⠀⠀⠻⠇⠀⠀⠀⠀⠀⠀⡱⣿⣻⣶⣄⠀⠉⠘⠛⠟⠿⣻⡿⢃⢐⡾⣡⣣⢈⢀⡽⢬⡛⢀⣭⠁⢈⣇⠘⠂⠀⠀⠀
⠀⠀⠀⠰⡗⠀⠀⠀⠀⠐⠇⠀⠀⠀⠀⠀⣼⣯⣿⡯⣿⣿⣿⣦⣀⠀⠀⠀⠉⠠⣏⣻⡱⢿⣻⡽⢸⣳⣴⠀⢈⡛⠀⠈⣙⠐⠿⠀⠀⠀
⠀⠀⠀⣰⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢽⡹⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⢫⣵⡮⠞⡫⢱⣷⣺⡿⠀⠸⠃⠀⠀⠛⠀⢾⠀⠀⠀
⠀⠀⠀⠄⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢄⢿⣺⣿⡿⣟⣿⣿⣿⠇⠀⠀⠀⠀⡠⣩⢢⠄⢠⣭⣟⣻⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⡌⣿⡿⢟⣿⣿⡙⠃⠀⠀⠀⠀⠘⢲⡇⣋⠀⠶⢟⡛⣟⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠣⢿⣿⠋⠃⠀⠀⠀⠀⠀⠀⠨⠈⠀⠀⠀⠀⠀⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡽⡄⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀⠀⠀⠀⠀⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠃⠀⣠⣶⣿⣿⣿⢻⠀⠀⠀⠀⠀⠀⠀⠈⠈⠀⣄⠀⣠⡴⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣯⣿⣿⣿⣿⡎⡇⠀⠀⠀⠀⠀⠀⠀⠄⢀⣯⣻⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢽⣿⣿⣿⣿⡾⡆⠀⠀⠀⠀⠀⠀⠀⢦⣽⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣇⡧⠀⠀⠀⠀⠀⠀⠀⣌⣿⢿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⢺⡆⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡿⠡⠿⣃⠀⠀⠀⠀⠀⠀⠝⣿⣿⣿⠿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠶⠶⣷⣷⣿⣭⡛⢇⠀⠀⠀⢀⣔⣫⣴⣷⣦⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠠⢠⡬⣄⣶⣍⢻⣿⣿⣿⣿⣿⣿⣎⠀⠀⢀⣴⣶⣦⡈⠹⣴⣭⠻⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠸⠺⠿⠿⠸⠿⠿⠿⠿⠿⠿⠋⠀⠀⠀⠸⠿⠿⠀⠀⠸⠪⠀⠸⠿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
You are dead)" << std::endl;
}

sf::Texture* Core::getCurrentFrame(){
    return fm->getFrame();
}
