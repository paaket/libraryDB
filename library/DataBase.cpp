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

void DataBase::addBook(const Book& book) {
    enteredDataBase.push_back(book);
}

void DataBase::getDataBase() {
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(dataBase, "SELECT * FROM books;", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::string errMsg = sqlite3_errmsg(dataBase);
        throw std::runtime_error("select error: " + errMsg);
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Book book;
        const unsigned char* bookName = sqlite3_column_text(stmt, 0);
        const unsigned char* authorFirst = sqlite3_column_text(stmt, 1);
        const unsigned char* authorLast = sqlite3_column_text(stmt, 2);
        int year = sqlite3_column_int(stmt, 3);
        const unsigned char* genre = sqlite3_column_text(stmt, 4);
        int pagesCount = sqlite3_column_int(stmt, 5);
        double rating = sqlite3_column_double(stmt, 6);

        book.bookName = reinterpret_cast<const char*>(bookName);
        book.authorFirst = reinterpret_cast<const char*>(authorFirst);
        book.authorLast = reinterpret_cast<const char*>(authorLast);
        book.year = year;
        book.genre = reinterpret_cast<const char*>(genre);
        book.pagesCount = pagesCount;
        book.rating = rating;

        addBook(book);
    }
    sqlite3_finalize(stmt);
}

void DataBase::printBookInfo(const Book& book) {
    std::cout << std::left << std::setw(50) << book.bookName << std::setw(20) << book.authorFirst << std::setw(25) << book.authorLast
        << std::setw(5) << book.year << std::setw(15) << book.genre << std::setw(6) << book.pagesCount << std::setw(7)
        << book.rating << std::endl;
}

void DataBase::printDataBase() {
    std::cout << std::left << std::setw(50) << "bookName" << std::setw(20) << "authorFirst" << std::setw(25) << "authorLast"
        << std::setw(5) << "year" << std::setw(15) << "genre" << std::setw(6) << "pages" << std::setw(7) << "rating" << std::endl;
    for (const auto& el : enteredDataBase)
        printBookInfo(el);
}