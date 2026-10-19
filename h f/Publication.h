#pragma once
#include <iostream>
#include <string>

class Publication {
private:
    int id;
    std::string title;
    int year;

public:
    Publication(int pubId, const std::string& pubTitle, int pubYear);

    virtual ~Publication() = default;

    int getId() const;
    std::string getTitle() const;
    int getYear() const;

    virtual std::string getType() const = 0;

    virtual void print(std::ostream& out) const;  
    virtual void read(std::istream& in);          

    void printShort() const;  

    bool operator==(const Publication& other) const;
    bool operator!=(const Publication& other) const;
    bool operator<(const Publication& other) const;
};

std::ostream& operator<<(std::ostream& out, const Publication& pub);
std::istream& operator>>(std::istream& in, Publication& pub);
