#include "Library.h"
#include "Logger.h"
#include "Student.h"
#include "External.h"
#include "Faculty.h"
#include "Validation.h"

#include <algorithm>
#include <ctime>
#include <fstream>

void Library::showAllMembers() {
    if (members.empty()) {
        cout << "No members found.\n";
        return;
    }

    cout << "\n--- ALL MEMBERS ---\n";
    for (auto m : members) {
        cout << "ID: " << m->getID()
             << " | Name: " << m->getName() << endl;
    }
}

void Library::saveBooks() {
    ofstream file("books.txt");

    for (auto b : books) {
        file << b->getISBN() << ","
             << b->getTitle() << ","
             << b->getAvailable() << endl;
    }

    file.close();
}

void Library::loadBooks() {
    ifstream file("books.txt");

    string isbn, title;
    int available;

    while (getline(file, isbn, ',')) {
        getline(file, title, ',');
        file >> available;
        file.ignore();

        Book* b = new Book(isbn, title, "Unknown", "CS", available);
        books.push_back(b);
    }

    file.close();
}

void Library::saveMembers() {
    ofstream file("members.txt");

    for (auto m : members) {
        file << m->getID() << ","
             << m->getName() << endl;
    }

    file.close();
}

void Library::saveRecord(string action, string isbn, string member) {
    ofstream file("records.txt", ios::app);

    time_t now = time(0);
    string dt = ctime(&now);

    file << dt.substr(0, dt.length() - 1)
         << " | " << action
         << " | " << isbn
         << " | " << member << endl;

    file.close();
}

void Library::showAllBooks() {
    if (books.empty()) {
        cout << "No books available in library." << endl;
        return;
    }

    cout << "\n--- All Books ---\n";
    for (auto b : books) {
        cout << "ISBN: " << b->getISBN()
             << " | Title: " << b->getTitle()
             << " | Available: " << b->getAvailable() << endl;
    }
}

void Library::removeBook(string isbn) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i]->getISBN() == isbn) {
            cout << "Book removed: " << books[i]->getTitle() << endl;
            books.erase(books.begin() + i);
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void Library::searchBook(string keyword) {
    if (books.empty()) {
        cout << "No books available." << endl;
        return;
    }

    cout << "\n--- Search Results ---\n";
    bool found = false;

    for (auto b : books) {
        if (b->getISBN() == keyword || b->getTitle() == keyword) {
            cout << "Found: " << b->getTitle()
                 << " (ISBN: " << b->getISBN() << ")\n";
            found = true;
        }
    }

    if (!found)
        cout << "No book found." << endl;
}

void Library::addBook(Book* b) {
    // Check duplicate ISBN
    for (auto existing : books) {
        if (existing->getISBN() == b->getISBN()) {
            cout << "Book with this ISBN already exists!" << endl;
            return;
        }
    }

    books.push_back(b);
    cout << "Book added successfully!" << endl;
}

void Library::addMember(Member* m) {
    members.push_back(m);
}

Book* Library::findBook(string isbn) {
    for (auto b : books) {
        if (b->getISBN() == isbn)
            return b;
    }
    return NULL;
}

void Library::issueBook(string isbn, Member* m) {
    Book* b = findBook(isbn);

    if (!b) {
        cout << "Book not found!\n";
        return;
    }

    if (b->getAvailable() > 0) {
        b->issueBook();

        Logger::getInstance()->log(m->getName() + " issued " + b->getTitle());

        saveRecord("ISSUE", isbn, m->getName());

        // NEW FILE LOG
        ofstream file("issued_books.txt", ios::app);
        time_t now = time(0);
        string dt = ctime(&now);

        file << dt.substr(0, dt.length() - 1)
             << " | " << m->getName()
             << " | " << isbn
             << " | " << b->getTitle()
             << endl;

        file.close();

    } else {
        cout << "Book not available. Reserved.\n";
        b->addReservation(m);
    }
}

void Library::returnBook(string isbn, Member* m) {
    Book* b = findBook(isbn);

    if (!b) {
        cout << "Book not found!\n";
        return;
    }

    b->returnBook();

    Logger::getInstance()->log(m->getName() + " returned " + b->getTitle());

    saveRecord("RETURN", isbn, m->getName());

    // NEW: Fine calculation
    int daysLate;
    cout << "Enter days late: ";
    daysLate = getValidInt();

    // Calculate fine
    double fine = daysLate * m->getFinePerDay();

    // Check for Faculty late return (more than 30 days)
    Faculty* fac = dynamic_cast<Faculty*>(m);
    if (fac != NULL && daysLate > 30) {
        cout << "ALERT: Faculty member returned book very late!\n";
        cout << "Notification sent to HoD\n";
    }

    cout << "Fine: Rs. " << fine << endl;
}