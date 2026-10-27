#include "Magazine.h"
using namespace std;

Magazine::Magazine(int magazineId, const string& magazineTitle, const string& magazinePublisher,
    int magazineYear, int magazineIssueNumber, const string& magazineTopic)
    : Publication(magazineId, magazineTitle, magazinePublisher, magazineYear),
    issueNumber(magazineIssueNumber), topic(magazineTopic) {}

int Magazine::getIssueNumber() const { return issueNumber; }
string Magazine::getTopic() const { return topic; }

void Magazine::printShort() const {
    Publication::printShort();
    cout << "    Журнал: выпуск №" << issueNumber << ", тематика: " << topic << "\n";
}

void Magazine::print(ostream& out) const {
    Publication::print(out);
    out << "Тип: журнал\n";
    out << "Номер выпуска: " << issueNumber << "\n";
    out << "Тематика: " << topic << "\n";
}
