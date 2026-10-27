#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Publication.h"

class Branch {
private:
    std::string name;
    int capacity;
    std::vector<std::unique_ptr<Publication>> catalog;

public:
    Branch(const std::string& branchName, int branchCapacity);

    const Publication* findPublicationById(int id) const;
    bool isFull() const;

    std::string getName() const;
    int getCapacity() const;
    int getPublicationsCount() const;

    void printCatalog() const;
    void printShort() const;

    int printOtherPublicationsBySamePublisher(const Publication& ref) const;
    int printPublicationsUpToYear(const Publication& ref) const;    
    int printPublicationsAfterYear(const Publication& ref) const;   

    Branch& operator+=(std::unique_ptr<Publication> publication);
    Branch& operator-=(const Publication& publication);
};
