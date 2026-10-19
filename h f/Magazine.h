#pragma once

#include <string>
#include "Publication.h"

class Magazine : public Publication {
private:
    int issueNumber; //номер выпуска
    std::string topic; //тема

public:
    Magazine(int magId, const std::string& magTitle, int magYear,
        int magIssueNumber, const std::string& magTopic);

    int getIssueNumber() const;
    std::string getTopic() const;

    std::string getType() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
};
