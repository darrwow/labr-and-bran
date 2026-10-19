#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Book.h"
#include "Publication.h"

class Branch {
private:
    std::string name;
    int capacity;
    std::vector<std::unique_ptr<Publication>> catalog;

public:
    Branch(const std::string& branchName, int branchCapacity);

    bool addPublication(std::unique_ptr<Publication> pub);
    bool removeById(int id);
    const Publication* findById(int id) const;
    bool isFull() const;

    std::string getName() const;
    int getCapacity() const;
    int getCount() const;

    void printCatalog() const;
    void printShort() const;
    int printOtherBooksBySameAuthor(const Book& ref) const;
    const Publication* newest() const;

    Branch& operator+=(std::unique_ptr<Publication> pub);
    Branch& operator-=(const Publication& pub);
};
