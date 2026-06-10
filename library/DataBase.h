#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "sqlite3.h"

class DataBase {
public:
    struct Book {
        std::string bookName;
        std::string authorFirst;
        std::string authorLast;
        int year;
        std::string genre;
        int pagesCount;
        double rating;
    };
    DataBase(const std::string& fileName);
    ~DataBase();
    void getDataBase();
    void addBook(const Book& book);
    void printBookInfo(const Book& book);
    void printDataBase();
private:
    sqlite3* dataBase = nullptr;
    std::vector<Book> enteredDataBase;
};
