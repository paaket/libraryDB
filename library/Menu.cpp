#include "Menu.h"

void Menu::start(const DataBase& dataBase) {
	bool flag = true;
	while (flag) {
		int option;
		std::cout << "\nMAIN MENU:\n1 - print data base\n2 - exit\noption: ";
		std::cin >> option;
		switch (option) {
		case 1: dataBase.printDataBase(); break;
		case 2: flag = false; break;
		}
	}
}