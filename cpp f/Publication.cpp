#include "Publication.h"

using namespace std;

Publication::Publication(int pubId, const string& pubTitle, int pubYear)
    : id(pubId), title(pubTitle), year(pubYear) {}

int Publication::getId() const { return id; }
string Publication::getTitle() const { return title; }
int Publication::getYear() const { return year; }

void Publication::print(ostream& out) const {
    out << "ID: " << id << "\n";
    out << "Тип: " << getType() << "\n";  
    out << "Название: " << title << "\n";
    out << "Год: " << year << "\n";
}

void Publication::read(istream& in) {
    getline(in, title);
    in >> year;
    in.ignore(1000, '\n');
}

void Publication::printShort() const {
    cout << "  ID " << id << ": [" << getType() << "] \"" << title << "\", " << year << "\n";
}

bool Publication::operator==(const Publication& other) const { return id == other.id; }
bool Publication::operator!=(const Publication& other) const { return !(*this == other); }
bool Publication::operator<(const Publication& other) const { return id < other.id; }

ostream& operator<<(ostream& out, const Publication& pub) {
    pub.print(out);
    return out;
}

istream& operator>>(istream& in, Publication& pub) {
    pub.read(in);
    return in;
}
