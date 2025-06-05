#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include <unordered_set>
#include <string>

class Room;

class RoomManager{
private:
    std::unordered_set<Room*> all_rooms;
public:
    RoomManager();
    void addConnection(Room* r1, Room* r2);
    void removeConnection(Room* r1, Room* r2);    
    Room* getRoom(std::string name);
    std::unordered_set<Room*> getAllRooms(){return all_rooms;}
    ~RoomManager();
};

#endif
