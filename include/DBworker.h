#ifndef DB_WORKER_H
#define DB_WORKER_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

class DBworker {
private:
    sqlite3* db;

public:
    DBworker(const std::string& database);

    std::string getAnimatronicStartRoom(const std::string& name, int night);
    
    int getAnimatronicActivity(const std::string& name, int night);

    ~DBworker();
};

#endif
