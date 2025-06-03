#include "G_Freddy.h"
#include "Animatronic.h"
#include "Room.h"
#include "MoveManager.h"
#include <vector>
#include <random>
#include <algorithm>


Room* G_Freddy::ai() {
    if (false) {
        std::unordered_set<Room*> rooms = current_room->getConnectedRooms();

        for (Room* room : rooms) {
            if (room->getName() == "Security Room") {
                return room;
            }
        }
    }

    return current_room;
}
