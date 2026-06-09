#include <iostream>
#include "DataBase.h"
#include "sqlite3.h"

int main() {
    sqlite3* db;
    
    DataBase dataBase;

    sqlite3_close(db);
    return 0;
}