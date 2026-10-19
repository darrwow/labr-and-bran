#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Book.h"
#include "Branch.h"
#include "Magazine.h"
#include "Newspaper.h"
#include "Publication.h"

using namespace std;

int readInt(const string& prompt) {
    cout << prompt;
    int number;
    if (!(cin >> number)) {
        cin.clear();  
        number = -1;
    }
    cin.ignore(1000, '\n');
    return number;
}

void printBranches(const vector<Branch>& branches) {
    for (size_t i = 0; i < branches.size(); ++i) {
        cout << i + 1 << ". ";
        branches[i].printShort();
    }
}

const Publication* findPublication(const vector<Branch>& branches, int id) {
    for (const Branch& branch : branches) {
        const Publication* pub = branch.findById(id);
        if (pub != nullptr) {
            return pub;
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
    const Publication* pub = findPublication(branches, id);
    if (pub == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    cout << *pub; 
}

void addPublication(vector<Branch>& branches, int& nextId) {
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

    cout << "Тип издания: 1 - книга, 2 - журнал, 3 - газета\n";
    int type = readInt("Выберите тип: ");

    
    unique_ptr<Publication> pub;
    if (type == 1) {
        pub = make_unique<Book>(nextId, "", 0, "", 0);
        cout << "Введите (каждое с новой строки): название, год, автор, число страниц\n";
    }
    else if (type == 2) {
        pub = make_unique<Magazine>(nextId, "", 0, 0, "");
        cout << "Введите (каждое с новой строки): название, год, номер выпуска, тематика\n";
    }
    else if (type == 3) {
        pub = make_unique<Newspaper>(nextId, "", 0, "", 0);
        cout << "Введите (каждое с новой строки): название, год, дата выпуска, тираж\n";
    }
    else {
        cout << "Такого типа нет.\n";
        return;
    }

    cin >> *pub; 
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ошибка ввода: число введено неверно. Издание не добавлено.\n";
        return;
    }

    branches[index] += move(pub);  
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
    const Publication* pub = branches[index].findById(id);
    if (pub == nullptr) {
        cout << "Издания с таким ID в этом филиале нет.\n";
        return;
    }
    branches[index] -= *pub;  
}

void showSameAuthor(const vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID книги: ");
    const Publication* pub = findPublication(branches, id);
    if (pub == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }

    const Book* book = dynamic_cast<const Book*>(pub);
    if (book == nullptr) {
        cout << "У издания типа \"" << pub->getType() << "\" нет автора.\n";
        return;
    }
    cout << "Другие книги автора " << book->getAuthor() << ":\n";
    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printOtherBooksBySameAuthor(*book);
    }
    if (total == 0) {
        cout << "  Других книг этого автора нет.\n";
    }
}

void showNewest(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        cout << branch.getName() << ": ";
        const Publication* newest = branch.newest();
        if (newest == nullptr) {
            cout << "изданий нет\n";
        }
        else {
            cout << "последнее поступление - " << newest->getType() << " \""
                << newest->getTitle() << "\" (ID " << newest->getId() << ")\n";
        }
    }
}

// Демонстрация наследования
void demoInheritance() {
    Book book(100, "Мастер и Маргарита", 1967, "М.А. Булгаков", 480);
    Magazine magazine(101, "Наука и жизнь", 2024, 7, "Научно-популярный");
    Newspaper newspaper(102, "Звязда", 2026, "19.10.2026", 15000);

    cout << "\n--- Унаследованные методы ---\n";
    cout << "Книга:   ID " << book.getId() << ", \"" << book.getTitle() << "\", " << book.getYear() << "\n";
    cout << "Журнал:  ID " << magazine.getId() << ", \"" << magazine.getTitle() << "\", " << magazine.getYear() << "\n";
    cout << "Газета:  ID " << newspaper.getId() << ", \"" << newspaper.getTitle() << "\", " << newspaper.getYear() << "\n";

    cout << "\n--- Собственные методы наследников ---\n";
    cout << "Книга:   автор " << book.getAuthor() << ", страниц " << book.getPages() << "\n";
    cout << "Журнал:  выпуск №" << magazine.getIssueNumber() << ", тематика " << magazine.getTopic() << "\n";
    cout << "Газета:  дата " << newspaper.getIssueDate() << ", тираж " << newspaper.getCirculation() << "\n";

    cout << "\n--- Переопределённые методы через указатель на базовый класс ---\n";
    const Publication* items[] = { &book, &magazine, &newspaper };
    for (const Publication* item : items) {
        cout << *item << "\n";
    }
}

void printMenu() {
    cout << "\n========== Сеть библиотек ==========\n";
    cout << "1. Показать филиалы и издания в них\n";
    cout << "2. Информация об издании\n";
    cout << "3. Добавить издание\n";
    cout << "4. Удалить издание\n";
    cout << "5. Другие книги того же автора\n";
    cout << "6. Последнее поступление в каждом филиале\n";
    cout << "7. Демонстрация наследования\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
}

int main() {
    vector<Branch> branches;
    branches.emplace_back("Филиал №1", 6);
    branches.emplace_back("Филиал №2", 6);

    int nextId = 1;
    branches[0].addPublication(make_unique<Book>(nextId++, "Война и мир", 1869, "Л.Н. Толстой", 1225));
    branches[0].addPublication(make_unique<Book>(nextId++, "Мастер и Маргарита", 1967, "М.А. Булгаков", 480));
    branches[0].addPublication(make_unique<Magazine>(nextId++, "Наука и жизнь", 2024, 7, "Научно-популярный"));
    branches[1].addPublication(make_unique<Book>(nextId++, "Анна Каренина", 1877, "Л.Н. Толстой", 864));
    branches[1].addPublication(make_unique<Newspaper>(nextId++, "Звязда", 2026, "19.10.2026", 15000));
    branches[1].addPublication(make_unique<Magazine>(nextId++, "Вокруг света", 2025, 3, "Путешествия"));

    cout << "Загружены тестовые данные: 2 филиала.\n";

    int choice;
    do {
        printMenu();
        choice = readInt("Выберите пункт меню: ");
        switch (choice) {
        case 1: showBranches(branches); break;
        case 2: showPublicationInfo(branches); break;
        case 3: addPublication(branches, nextId); break;
        case 4: deletePublication(branches); break;
        case 5: showSameAuthor(branches); break;
        case 6: showNewest(branches); break;
        case 7: demoInheritance(); break;
        case 0: cout << "Завершение работы.\n"; break;
        default: cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);

    return 0;
}
