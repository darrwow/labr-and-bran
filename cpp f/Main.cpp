#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Publication.h"
#include "Book.h"
#include "Magazine.h"
#include "Newspaper.h"
#include "Branch.h"
using namespace std;

int readInt(const string& prompt) {
    cout << prompt;
    int number;
    cin >> number;
    cin.ignore(1000, '\n');
    return number;
}

string readLine(const string& prompt) {
    cout << prompt;
    string text;
    getline(cin, text);
    return text;
}

void printBranches(const vector<Branch>& branches) {
    for (size_t i = 0; i < branches.size(); ++i) {
        cout << i + 1 << ". ";
        branches[i].printShort();
    }
}

const Publication* findPublication(const vector<Branch>& branches, int id) {
    for (const Branch& branch : branches) {
        const Publication* publication = branch.findPublicationById(id);
        if (publication != nullptr) {
            return publication;
        }
    }
    return nullptr;
}

void showBranches(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        branch.printCatalog();
    }
}

void showPublicationInfo(const vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID издания: ");
    const Publication* publication = findPublication(branches, id);
    if (publication == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    cout << *publication; 
}

void addPublication(vector<Branch>& branches, int& nextId) {
    cout << "Какой тип издания добавить?\n";
    cout << "1. Книга\n2. Журнал\n3. Газета\n4. Обычное издание\n";
    int type = readInt("Тип: ");
    if (type < 1 || type > 4) {
        cout << "Некорректный тип.\n";
        return;
    }

    Publication common(nextId, "", "", 0);
    cout << "Введите название, издательство и год издания (каждое с новой строки):\n";
    cin >> common; // оператор >>

    unique_ptr<Publication> publication;
    if (type == 1) {
        string author = readLine("Автор: ");
        int pages = readInt("Количество страниц: ");
        string genre = readLine("Жанр: ");
        publication = make_unique<Book>(nextId, common.getTitle(), common.getPublisher(),
            common.getYear(), author, pages, genre);
    }
    else if (type == 2) {
        int issue = readInt("Номер выпуска: ");
        string topic = readLine("Тематика: ");
        publication = make_unique<Magazine>(nextId, common.getTitle(), common.getPublisher(),
            common.getYear(), issue, topic);
    }
    else if (type == 3) {
        int circulation = readInt("Тираж: ");
        string city = readLine("Город выпуска: ");
        publication = make_unique<Newspaper>(nextId, common.getTitle(), common.getPublisher(),
            common.getYear(), circulation, city);
    }
    else {
        publication = make_unique<Publication>(nextId, common.getTitle(), common.getPublisher(),
            common.getYear());
    }

    cout << "В какой филиал добавить?\n";
    printBranches(branches);
    int choice = readInt("Номер филиала: ");
    if (choice < 1 || choice > static_cast<int>(branches.size())) {
        cout << "Некорректный номер.\n";
        return;
    }
    int index = choice - 1;
    if (branches[index].isFull()) {
        cout << "Филиал \"" << branches[index].getName() << "\" переполнен.\n";
        return;
    }
    branches[index] += std::move(publication); // оператор +=
    nextId++;
}

void deletePublication(vector<Branch>& branches) {
    printBranches(branches);
    int choice = readInt("Из какого филиала удалить издание: ");
    if (choice < 1 || choice > static_cast<int>(branches.size())) {
        cout << "Некорректный номер.\n";
        return;
    }
    int index = choice - 1;
    branches[index].printCatalog();
    int id = readInt("Введите ID издания для удаления: ");
    const Publication* publication = findPublication(branches, id);
    if (publication == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    Publication copy = *publication; 
    branches[index] -= copy; // оператор -=
}

void showSamePublisher(const vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID издания: ");
    const Publication* publication = findPublication(branches, id);
    if (publication == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    cout << "Другие издания издательства " << publication->getPublisher() << ":\n";
    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printOtherPublicationsBySamePublisher(*publication);
    }
    if (total == 0) {
        cout << " Других изданий этого издательства нет.\n";
    }
}

void showUpToYear(const vector<Branch>& branches) {
    int year = readInt("Введите год: ");
    Publication ref(0, "", "", year);

    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printPublicationsUpToYear(ref);
    }

    if (total == 0) {
        cout << "Таких изданий нет.\n";
    }
}

void showAfterYear(const vector<Branch>& branches) {
    int year = readInt("Введите год: ");
    Publication ref(0, "", "", year);

    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printPublicationsAfterYear(ref);
    }

    if (total == 0) {
        cout << "Таких изданий нет.\n";
    }
}

void printMenu() {
    cout << "\n========== Сеть библиотек ==========\n";
    cout << "1. Показать филиалы и издания в них\n";
    cout << "2. Информация об издании\n";
    cout << "3. Добавить издание\n";
    cout << "4. Удалить издание\n";
    cout << "5. Другие издания того же издательства\n";
    cout << "6. Издания, вышедшие в указанном году и раньше\n";
    cout << "7. Издания, вышедшие после указанного года\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
}

int main() {
    vector<Branch> branches;
    branches.emplace_back("Филиал №1", 5);
    branches.emplace_back("Филиал №2", 5);

    int nextId = 1;
    branches[0] += make_unique<Book>(nextId++, "Война и мир", "Азбука", 1869, "Л.Н. Толстой", 1300, "роман");
    branches[0] += make_unique<Book>(nextId++, "Мастер и Маргарита", "Эксмо", 1967, "М.А. Булгаков", 480, "роман");
    branches[0] += make_unique<Magazine>(nextId++, "Наука и жизнь", "Правда", 2023, 5, "наука");

    branches[1] += make_unique<Book>(nextId++, "Евгений Онегин", "Азбука", 1833, "А.С. Пушкин", 240, "роман в стихах");
    branches[1] += make_unique<Newspaper>(nextId++, "Вечерний Минск", "Минская правда", 2024, 25000, "Минск");
    branches[1] += make_unique<Publication>(nextId++, "Справочник библиотекаря", "Эксмо", 2010);

    int choice;
    do {
        printMenu();
        choice = readInt("Выберите пункт меню: ");
        switch (choice) {
        case 1: showBranches(branches); break;
        case 2: showPublicationInfo(branches); break;
        case 3: addPublication(branches, nextId); break;
        case 4: deletePublication(branches); break;
        case 5: showSamePublisher(branches); break;
        case 6: showUpToYear(branches); break;
        case 7: showAfterYear(branches); break;
        case 0: cout << "Завершение работы.\n"; break;
        default: cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);

    return 0;
}
