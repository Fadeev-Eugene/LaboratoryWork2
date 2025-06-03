#include "DBworker.h"
#include <iostream>
#include <algorithm>

DBworker::DBworker(const std::string& database){
    int rc = sqlite3_open(database.c_str(), &db);
    if (rc) {
        std::cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "База данных открыта успешно!" << std::endl;
    }
}


std::string DBworker::getAnimatronicStartRoom(const std::string& name, int night){
    sqlite3_stmt *stmt;
    std::string result = "";

    const char *sql = "SELECT Room_name FROM Rooms WHERE (ID == (SELECT Start_room FROM Info WHERE (Animatronic == (SELECT ID FROM Animatronics WHERE Name == ?)) AND (Night == ?)));";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << std::endl;
        return result;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, night);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *text = sqlite3_column_text(stmt, 0);
        result = text ? reinterpret_cast<const char *>(text) : "";
    } else {
        std::cerr << "Нет данных или ошибка запроса." << std::endl;
    }

    sqlite3_finalize(stmt);

    return result; 
}


int DBworker::getAnimatronicActivity(const std::string& name, int night){
    sqlite3_stmt *stmt;
    int result = -1;

    const char *sql = "SELECT Night_activity FROM Info WHERE (Animatronic == (SELECT ID FROM Animatronics WHERE Name == ?)) AND (Night == ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << std::endl;
        return result;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, night);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    } else {
        std::cerr << "Нет данных или ошибка запроса." << std::endl;
    }

    sqlite3_finalize(stmt);

    return result;
}


std::string DBworker::getCurrentFrame(Room* room) {
    sqlite3_stmt* stmt = nullptr;
    std::string frame = "default_frame";
    std::string roomName = room->getName();
    auto animatronics = room->getAnimatronics();

    const std::vector<std::string> allAnims = {"Foxy", "Freddy Fazbear", "Bonnie", "Chica"};

    std::vector<std::string> presentAnims;
    for (const auto& anim : allAnims) {
        if (std::any_of(animatronics.begin(), animatronics.end(), 
            [&](Animatronic* a) { return a->getName() == anim; })) {
            presentAnims.push_back(anim);
        }
    }

    std::string exactConditions;
    for (const auto& anim : allAnims) {
        bool isPresent = std::any_of(animatronics.begin(), animatronics.end(), 
            [&](Animatronic* a) { return a->getName() == anim; });
        exactConditions += "[" + anim + "] = \"" + (isPresent ? "TRUE" : "FALSE") + "\" AND ";
    }
    if (!exactConditions.empty()) {
        exactConditions = exactConditions.substr(0, exactConditions.size() - 5);
    }

    std::string exactQuery = 
        "SELECT Img FROM Corr_img "
        "WHERE Camera = (SELECT ID FROM Rooms WHERE Room_name = ?) "
        "AND " + exactConditions + " "
        "ORDER BY RANDOM() LIMIT 1";

    if (sqlite3_prepare_v2(db, exactQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, roomName.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            frame = text ? reinterpret_cast<const char*>(text) : "default_frame";
            sqlite3_finalize(stmt);
            return frame;
        }
        sqlite3_finalize(stmt);
    }

    for (const auto& targetAnim : presentAnims) {
        std::string fallbackConditions;
        for (const auto& anim : allAnims) {
            bool isPresent = (anim == targetAnim);
            fallbackConditions += "[" + anim + "] = \"" + (isPresent ? "TRUE" : "FALSE") + "\" AND ";
        }
        fallbackConditions = fallbackConditions.substr(0, fallbackConditions.size() - 5);

        std::string fallbackQuery = 
            "SELECT Img FROM Corr_img "
            "WHERE Camera = (SELECT ID FROM Rooms WHERE Room_name = ?) "
            "AND " + fallbackConditions + " "
            "ORDER BY RANDOM() LIMIT 1";

        if (sqlite3_prepare_v2(db, fallbackQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, roomName.c_str(), -1, SQLITE_STATIC);
            
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                const unsigned char* text = sqlite3_column_text(stmt, 0);
                frame = text ? reinterpret_cast<const char*>(text) : "default_frame";
                sqlite3_finalize(stmt);
                return frame;
            }
            sqlite3_finalize(stmt);
        }
    }

    std::string emptyCameraConditions;
    for (const auto& anim : allAnims) {
        emptyCameraConditions += "[" + anim + "] = \"FALSE\" AND ";
    }
    emptyCameraConditions = emptyCameraConditions.substr(0, emptyCameraConditions.size() - 5);

    std::string emptyCameraQuery = 
        "SELECT Img FROM Corr_img "
        "WHERE Camera = (SELECT ID FROM Rooms WHERE Room_name = ?) "
        "AND " + emptyCameraConditions + " "
        "ORDER BY RANDOM() LIMIT 1";
    if (sqlite3_prepare_v2(db, emptyCameraQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, roomName.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            frame = text ? reinterpret_cast<const char*>(text) : "default_frame";
            sqlite3_finalize(stmt);
            return frame;
        }
        sqlite3_finalize(stmt);
    }

    return frame;
}

DBworker::~DBworker(){
    if (db) {
        sqlite3_close(db);
    }
}
