#pragma once
#include <iostream>
#include <string>
#include "Publication.h"

class Magazine : public Publication {
private:
    int issueNumber;
    std::string topic;

public:
    Magazine(int magazineId, const std::string& magazineTitle, const std::string& magazinePublisher,
        int magazineYear, int magazineIssueNumber, const std::string& magazineTopic);

    int getIssueNumber() const;
    std::string getTopic() const;

    void printShort() const override;
    void print(std::ostream& out) const override;
};
