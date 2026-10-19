#pragma once

#include <string>
#include "Publication.h"

class Newspaper : public Publication {
private:
    std::string issueDate; //дата выпуска
    int circulation; //тираж

public:
    Newspaper(int newsId, const std::string& newsTitle, int newsYear,
        const std::string& newsIssueDate, int newsCirculation);

    std::string getIssueDate() const;
    int getCirculation() const;

    std::string getType() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in) override;
};
