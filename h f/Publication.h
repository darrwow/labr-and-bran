#pragma once
#include <iostream>
#include <string>

class Publication {
private:
    int id;
    std::string title;
    std::string publisher;
    int year;

public:
    Publication(int publicationId, const std::string& publicationTitle, const std::string& publicationPublisher, int publicationYear);

    virtual ~Publication() = default;

    int getId() const;
    std::string getTitle() const;
    std::string getPublisher() const;
    int getYear() const;

    virtual void printShort() const;                 
    virtual void print(std::ostream& out) const;      

    bool operator==(const Publication& other) const;
    bool operator<=(const Publication& other) const;
    bool operator>(const Publication& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Publication& publication) {
        publication.print(out);
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Publication& publication) {
        std::getline(in, publication.title);
        std::getline(in, publication.publisher);
        in >> publication.year;
        in.ignore(1000, '\n');
        return in;
    }

    friend bool samePublisher(const Publication& a, const Publication& b);
};
