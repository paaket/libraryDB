#include "DataBase.h"

DataBase::DataBase(const std::string& fileName) {
    int rc = sqlite3_open(fileName.c_str(), &dataBase);
    if (rc != SQLITE_OK) {
        std::string errMsg = sqlite3_errmsg(dataBase);
        throw std::runtime_error("open error: " + errMsg);
    }
}

DataBase::~DataBase() {
    sqlite3_close(dataBase);
}

void DataBase::printDataBase() const {
    sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(dataBase, "SELECT * FROM books;", -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string errMsg = sqlite3_errmsg(dataBase);
            throw std::runtime_error("printDataBase() error: " + errMsg);
        }
        
        std::cout << "\n" << std::left << std::setw(3) << "id" << std::setw(45) << "bookName" << std::setw(25) << "authorFirst" 
            << std::setw(25) << "authorLast" << std::setw(5) << "year" << std::setw(15) << "genre" << std::setw(6) << "pages" 
            << std::setw(7) << "rating" << std::endl;

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* bookName = sqlite3_column_text(stmt, 1);
            const unsigned char* authorFirst = sqlite3_column_text(stmt, 2);
            const unsigned char* authorLast = sqlite3_column_text(stmt, 3);
            int year = sqlite3_column_int(stmt, 4);
            const unsigned char* genre = sqlite3_column_text(stmt, 5);
            int pagesCount = sqlite3_column_int(stmt, 6);
            double rating = sqlite3_column_double(stmt, 7);
            
            std::cout << std::left << std::setw(3) << id << std::setw(45) << bookName << std::setw(25) << authorFirst 
                << std::setw(25) << authorLast << std::setw(5) << year << std::setw(15) << genre << std::setw(6) << pagesCount 
                << std::setw(7) << rating << std::endl;
        }
        sqlite3_finalize(stmt);
}

void safelyGetInt(int& a) {
    std::cin >> a;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "cin error! enter new value: ";
        std::cin >> a;
    }
}

void safelyGetDouble(double& a) {
    std::cin >> a;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "cin error! enter new value: ";
        std::cin >> a;
    }
}

void DataBase::addBook() const {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(dataBase, "INSERT INTO books (bookName, authorFirst, authorLast, year, genre, pagesCount, rating) VALUES (?, ?, ?, ?, ?, ?, ?);", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::string errMsg = sqlite3_errmsg(dataBase);
        throw std::runtime_error("addBook() error: " + errMsg);
    }

    std::string bookName, authorFirst, authorLast, genre;
    int year, pagesCount;
    double rating;

    std::cin.ignore(1000, '\n');
    std::cout << "bookName: ";
    std::getline(std::cin, bookName);
    std::cout << "authorFirst: ";
    std::getline(std::cin, authorFirst);
    std::cout << "authorLast: ";
    std::getline(std::cin, authorLast);
    std::cout << "year: ";
    safelyGetInt(year);
    std::cin.ignore(1000, '\n');
    std::cout << "genre: ";
    std::getline(std::cin, genre);
    std::cout << "pagesCount: ";
    safelyGetInt(pagesCount);
    std::cout << "rating: ";
    safelyGetDouble(rating);

    sqlite3_bind_text(stmt, 1, bookName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, authorFirst.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, authorLast.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, year);
    sqlite3_bind_text(stmt, 5, genre.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, pagesCount);
    sqlite3_bind_double(stmt, 7, rating);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        std::cout << "successfully added" << std::endl;
        sqlite3_finalize(stmt);
    }
    else {
        sqlite3_finalize(stmt);
        std::string errMsg = sqlite3_errmsg(dataBase);
        throw std::runtime_error("addBook() error: " + errMsg);
    }
}

void DataBase::deleteBook() const {
    sqlite3_stmt* stmt;
    int idForRemove;

    std::cout << "enter id to delete: ";
    safelyGetInt(idForRemove);

    int rc = sqlite3_prepare_v2(dataBase, "SELECT * FROM books WHERE id = ?;", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::string errMsg = sqlite3_errmsg(dataBase);
        throw std::runtime_error("deleteBook() error: " + errMsg);
    }
    
    sqlite3_bind_int(stmt, 1, idForRemove);

   if (sqlite3_step(stmt) == SQLITE_ROW) {
       std::cout << "\n" << std::left << std::setw(3) << "id" << std::setw(45) << "bookName" << std::setw(25) << "authorFirst"
           << std::setw(25) << "authorLast" << std::setw(5) << "year" << std::setw(15) << "genre" << std::setw(6) << "pages"
           << std::setw(7) << "rating" << std::endl;
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* bookName = sqlite3_column_text(stmt, 1);
        const unsigned char* authorFirst = sqlite3_column_text(stmt, 2);
        const unsigned char* authorLast = sqlite3_column_text(stmt, 3);
        int year = sqlite3_column_int(stmt, 4);
        const unsigned char* genre = sqlite3_column_text(stmt, 5);
        int pagesCount = sqlite3_column_int(stmt, 6);
        double rating = sqlite3_column_double(stmt, 7);

        std::cout << std::left << std::setw(3) << id << std::setw(45) << bookName << std::setw(25) << authorFirst
            << std::setw(25) << authorLast << std::setw(5) << year << std::setw(15) << genre << std::setw(6) << pagesCount
            << std::setw(7) << rating << std::endl;
   }
   else {
       std::cout << "\nbook with this id not found" << std::endl;
       sqlite3_finalize(stmt);
       std::string errMsg = sqlite3_errmsg(dataBase);
       throw std::runtime_error("deleteBook() error: " + errMsg);
   }

   sqlite3_finalize(stmt);
   stmt = nullptr;

   std::string option;
   std::cout << "\ncontinue? (y/n): ";
   std::cin.ignore(1000, '\n');
   std::getline(std::cin, option);
   if (option == "y") {
       int rc = sqlite3_prepare_v2(dataBase, "DELETE FROM books WHERE id = ?;", -1, &stmt, nullptr);
       if (rc != SQLITE_OK) {
           std::string errMsg = sqlite3_errmsg(dataBase);
           throw std::runtime_error("deleteBook() error: " + errMsg);
       }
       sqlite3_bind_int(stmt, 1, idForRemove);
       if (sqlite3_step(stmt) == SQLITE_DONE) {
           std::cout << "successfully" << std::endl;
           sqlite3_finalize(stmt);
       }
       else {
           sqlite3_finalize(stmt);
           std::string errMsg = sqlite3_errmsg(dataBase);
           throw std::runtime_error("deleteBook() error: " + errMsg);
       }
   }
   else {
       std::cout << "cancellation" << std::endl;
       sqlite3_finalize(stmt);
   }
}