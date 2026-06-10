#include "Menu.h"

void Menu::start(const DataBase& dataBase) {
	bool flag = true;
	while (flag) {
		int option;
		std::cout << "\nMAIN MENU:\n1 - print data base\n2 - add book\n3 - delete book\n4 - exit\noption: ";
		std::cin >> option;
		switch (option) {
		case 1: dataBase.printDataBase(); break;
		case 2: dataBase.addBook(); break;
		case 3: dataBase.deleteBook(); break;
		case 4: flag = false; break;
		}
	}
}