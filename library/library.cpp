#include <iostream>
#include "DataBase.h"
#include "sqlite3.h"

int main() {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("booksLibrary.db", &db);
    if (rc != SQLITE_OK) {
        std::cout << "open error: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    DataBase dataBase;

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}