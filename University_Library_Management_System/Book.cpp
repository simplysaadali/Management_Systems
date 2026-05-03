#include "Book.h"
#include "Member.h"

Book::Book(string i, string t, string a, string c, int total) {
    isbn = i;
    title = t;
    author = a;
    category = c;
    totalCopies = total;
    availableCopies = total;
}

string Book::getISBN() { return isbn; }
string Book::getTitle() { return title; }
int Book::getAvailable() { return availableCopies; }

void Book::addReservation(Member* m) {
    reservedMembers.push_back(m);
}

void Book::notifyMembers() {
    if (availableCopies > 0) {
        for (auto m : reservedMembers) {
            cout << "Notification: Book available for " << m->getName() << endl;
        }
        reservedMembers.clear();
    }
}

void Book::issueBook() {
    if (availableCopies > 0)
        availableCopies--;
}

void Book::returnBook() {
    availableCopies++;
    notifyMembers(); // Observer pattern
}

bool Book::operator==(const Book& other) {
    return this->isbn == other.isbn;
}