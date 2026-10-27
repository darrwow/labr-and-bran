#include "Newspaper.h"
using namespace std;

Newspaper::Newspaper(int newspaperId, const string& newspaperTitle, const string& newspaperPublisher,
    int newspaperYear, int newspaperCirculation, const string& newspaperCity)
    : Publication(newspaperId, newspaperTitle, newspaperPublisher, newspaperYear),
    circulation(newspaperCirculation), city(newspaperCity) {}

int Newspaper::getCirculation() const { return circulation; }
string Newspaper::getCity() const { return city; }

void Newspaper::printShort() const {
    Publication::printShort();
    cout << "    Газета: тираж " << circulation << ", город выпуска: " << city << "\n";
}

void Newspaper::print(ostream& out) const {
    Publication::print(out);
    out << "Тип: газета\n";
    out << "Тираж: " << circulation << "\n";
    out << "Город выпуска: " << city << "\n";
}
