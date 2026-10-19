#include "Newspaper.h"

using namespace std;

Newspaper::Newspaper(int newsId, const string& newsTitle, int newsYear,
    const string& newsIssueDate, int newsCirculation)
    : Publication(newsId, newsTitle, newsYear), issueDate(newsIssueDate), circulation(newsCirculation) {}

string Newspaper::getIssueDate() const { return issueDate; }
int Newspaper::getCirculation() const { return circulation; }

string Newspaper::getType() const { return "Газета"; }

void Newspaper::print(ostream& out) const {
    Publication::print(out);
    out << "Дата выпуска: " << issueDate << "\n";
    out << "Тираж: " << circulation << "\n";
}

void Newspaper::read(istream& in) {
    Publication::read(in);
    getline(in, issueDate);
    in >> circulation;
    in.ignore(1000, '\n');
}
