#pragma once

#include <string>
#include "Publication.h"

class Book : public Publication {
private:
    std::string author;
    int pages;

public:
    Book(int bookId, const std::string& bookTitle, int bookYear,
        const std::string& bookAuthor, int bookPages);

    std::string getAuthor() const;
    int getPages() const;

    std::string getType() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;

    friend bool sameAuthor(const Book& a, const Book& b);
};

bool sameAuthor(const Book& a, const Book& b);
