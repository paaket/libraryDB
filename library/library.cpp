#include <iostream>
#include <string>
#include <cstdlib>
#include "DataBase.h"
#include "Menu.h"
#include "sqlite3.h"

int main() {
    std::string fileName;
    std::cout << "enter .db file name: ";
    std::getline(std::cin, fileName);
    
    try {
        DataBase dataBase(fileName);
        Menu menu;
        menu.start(dataBase);
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
        exit(1);
    }
    return 0;
}