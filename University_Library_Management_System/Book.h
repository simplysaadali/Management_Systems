#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <vector>
using namespace std;

class Member; // forward declaration

class Book {
private:
    string isbn, title, author, category;
    int totalCopies;
    int availableCopies;

    vector<Member*> reservedMembers;

public:
    Book(string i, string t, string a, string c, int total);

    string getISBN();
    string getTitle();
    int getAvailable();

    void addReservation(Member* m);

    vector<string> notifyMembers();

    void showReservations();

    void issueBook();
    void returnBook();

    bool operator==(const Book& other);
};

#endif