#pragma once
#include <iostream>
#include <string>
#include "Publication.h"

class Book : public Publication {
private:
    std::string author;
    int pages;
    std::string genre;

public:
    Book(int bookId, const std::string& bookTitle, const std::string& bookPublisher, int bookYear,
        const std::string& bookAuthor, int bookPages, const std::string& bookGenre);

    std::string getAuthor() const;
    int getPages() const;
    std::string getGenre() const;

    void printShort() const override;
    void print(std::ostream& out) const override;
};
