#pragma once
#include <string>

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
    void getDataBase();
private:

};
