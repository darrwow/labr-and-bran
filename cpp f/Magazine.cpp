#include "Magazine.h"

using namespace std;

Magazine::Magazine(int magId, const string& magTitle, int magYear,
    int magIssueNumber, const string& magTopic)
    : Publication(magId, magTitle, magYear), issueNumber(magIssueNumber), topic(magTopic) {}

int Magazine::getIssueNumber() const { return issueNumber; }
string Magazine::getTopic() const { return topic; }

string Magazine::getType() const { return "Журнал"; }

void Magazine::print(ostream& out) const {
    Publication::print(out);
    out << "Номер выпуска: " << issueNumber << "\n";
    out << "Тематика: " << topic << "\n";
}

void Magazine::read(istream& in) {
    Publication::read(in);
    in >> issueNumber;
    in.ignore(1000, '\n');
    getline(in, topic);
}
