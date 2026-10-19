#include "Book.h"

using namespace std;

Book::Book(int bookId, const string& bookTitle, int bookYear,
    const string& bookAuthor, int bookPages)
    : Publication(bookId, bookTitle, bookYear), author(bookAuthor), pages(bookPages) {}

string Book::getAuthor() const { return author; }
int Book::getPages() const { return pages; }

string Book::getType() const { return "Книга"; }

void Book::print(ostream& out) const {
    Publication::print(out);  
    out << "Автор: " << author << "\n";
    out << "Страниц: " << pages << "\n";
}

void Book::read(istream& in) {
    Publication::read(in);  
    getline(in, author);
    in >> pages;
    in.ignore(1000, '\n');
}

bool sameAuthor(const Book& a, const Book& b) {
    return a.author == b.author;
}
