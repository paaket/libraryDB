#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "sqlite3.h"

class DataBase {
public:
    DataBase(const std::string& fileName);
    ~DataBase();
    void printDataBase() const;
    void addBook() const;
private:
    sqlite3* dataBase = nullptr;
};
