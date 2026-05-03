#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "book.h"
#include "member.h"

class Library {
private:
    vector<Book*> books;
    vector<Member*> members;

public:
    void saveBooks();
    void loadBooks();
    void saveMembers();
    void showAllBooks();

    void addBook(Book* b);
    void addMember(Member* m);

    void saveRecord(string action, string isbn, string member);
    void removeBook(string isbn);
    void searchBook(string keyword);

    Book* findBook(string isbn);

    void issueBook(string isbn, Member* m);
    void returnBook(string isbn, Member* m);
};

#endif