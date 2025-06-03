#include "DBworker.h"

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


DBworker::~DBworker(){
    if (db) {
        sqlite3_close(db);
    }
}
