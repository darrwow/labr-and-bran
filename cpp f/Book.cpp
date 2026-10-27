#include "Book.h"
using namespace std;

Book::Book(int bookId, const string& bookTitle, const string& bookPublisher, int bookYear,
    const string& bookAuthor, int bookPages, const string& bookGenre)
    : Publication(bookId, bookTitle, bookPublisher, bookYear),   
    author(bookAuthor), pages(bookPages), genre(bookGenre) {}

string Book::getAuthor() const { return author; }
int Book::getPages() const { return pages; }
string Book::getGenre() const { return genre; }

void Book::printShort() const {
    Publication::printShort();  
    cout << "    Книга: " << author << ", " << pages << " стр., жанр: " << genre << "\n";
}

void Book::print(ostream& out) const {
    Publication::print(out);
    out << "Тип: книга\n";
    out << "Автор: " << author << "\n";
    out << "Страниц: " << pages << "\n";
    out << "Жанр: " << genre << "\n";
}
