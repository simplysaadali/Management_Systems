#include "Book.h"
#include "Member.h"

// Constructor
Book::Book(string i, string t, string a, string c, int total) {
    isbn = i;
    title = t;
    author = a;
    category = c;
    totalCopies = total;
    availableCopies = total;
}

// Getters
string Book::getISBN() { return isbn; }
string Book::getTitle() { return title; }
int Book::getAvailable() { return availableCopies; }

// Reserve book
void Book::addReservation(Member* m) {
    reservedMembers.push_back(m);
}

vector<string> Book::notifyMembers() {
    vector<string> notified;

    if (availableCopies > 0 && !reservedMembers.empty()) {
        cout << "\n🔔 Notifications:\n";

        for (auto m : reservedMembers) {
            string msg = "Book available for " + m->getName();
            cout << msg << endl;
            notified.push_back(m->getName());
        }

        reservedMembers.clear();
    }

    return notified;
}

// Show reserved users (optional debug/admin feature)
void Book::showReservations() {
    if (reservedMembers.empty()) {
        cout << "No reservations.\n";
        return;
    }

    cout << "\n--- Reserved Members ---\n";
    for (auto m : reservedMembers) {
        cout << m->getName() << endl;
    }
}

// Issue book
void Book::issueBook() {
    if (availableCopies > 0)
        availableCopies--;
}

// Return book
void Book::returnBook() {
    availableCopies++;
}

// Operator overloading
bool Book::operator==(const Book& other) {
    return this->isbn == other.isbn;
}