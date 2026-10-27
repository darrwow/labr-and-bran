#pragma once
#include <iostream>
#include <string>
#include "Publication.h"

class Newspaper : public Publication {
private:
    int circulation;
    std::string city;

public:
    Newspaper(int newspaperId, const std::string& newspaperTitle, const std::string& newspaperPublisher,
        int newspaperYear, int newspaperCirculation, const std::string& newspaperCity);

    int getCirculation() const;
    std::string getCity() const;

    void printShort() const override;
    void print(std::ostream& out) const override;
};
