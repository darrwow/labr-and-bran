#include "Branch.h"
#include <iostream>

using namespace std;

Branch::Branch(const string& branchName, int branchCapacity)
    : name(branchName), capacity(branchCapacity) {}

bool Branch::addPublication(unique_ptr<Publication> pub) {
    if (isFull()) {
        return false;
    }
    catalog.push_back(move(pub)); 
    return true;
}

bool Branch::removeById(int id) {
    for (size_t i = 0; i < catalog.size(); ++i) {
        if (catalog[i]->getId() == id) {
            catalog.erase(catalog.begin() + i);
            return true;
        }
    }
    return false;
}

const Publication* Branch::findById(int id) const {
    for (const std::unique_ptr<Publication>& pub : catalog) {
        if (pub->getId() == id) {
            return pub.get();
        }
    }
    return nullptr;
}

bool Branch::isFull() const {
    return static_cast<int>(catalog.size()) >= capacity;
}

string Branch::getName() const { return name; }
int Branch::getCapacity() const { return capacity; }
int Branch::getCount() const { return static_cast<int>(catalog.size()); }

void Branch::printCatalog() const {
    cout << "=== Филиал \"" << name << "\" (изданий: " << catalog.size()
        << "/" << capacity << ") ===\n";
    if (catalog.empty()) {
        cout << "  В филиале нет изданий.\n";
    }
    for (const auto& pub : catalog) {
        pub->printShort();
    }
}

void Branch::printShort() const {
    cout << name << " (изданий: " << catalog.size() << "/" << capacity << ")\n";
}

int Branch::printOtherBooksBySameAuthor(const Book& ref) const {
    int count = 0;
    for (const unique_ptr<Publication>& pub : catalog) {

        const Book* book = dynamic_cast<const Book*>(pub.get());
        if (book != nullptr && *book != ref && sameAuthor(*book, ref)) {
            cout << name << ":";
            book->printShort();
            count++;
        }
    }
    return count;
}

const Publication* Branch::newest() const {
    const Publication* result = nullptr;
    for (const std::unique_ptr<Publication>&pub : catalog) {
        if (result == nullptr || *result < *pub) {
            result = pub.get();
        }
    }
    return result;
}

Branch& Branch::operator+=(unique_ptr<Publication> pub) {
    if (isFull()) {
        cout << "Ошибка: филиал \"" << name << "\" переполнен.\n";
        return *this;
    }
    cout << "Добавлено (" << pub->getType() << "): \"" << pub->getTitle() << "\" - филиал \"" << name << "\".\n";
    catalog.push_back(move(pub));
    return *this;
}

Branch& Branch::operator-=(const Publication& pub) {
    for (size_t i = 0; i < catalog.size(); ++i) {
        if (*catalog[i] == pub) {
            string type = pub.getType();
            string title = pub.getTitle();
            catalog.erase(catalog.begin() + i);
            cout << "Удалено (" << type << "): \"" << title << "\" - филиал \"" << name << "\".\n";
            return *this;
        }
    }
    cout << "Ошибка: такого издания нет в филиале \"" << name << "\".\n";
    return *this;
}
