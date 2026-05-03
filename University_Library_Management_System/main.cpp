#include "Library.h"
#include "MemberFactory.h"
#include "Validation.h"

int main() {
    Library lib;

    lib.loadBooks();

    // sample member
    Member* m = NULL;
    Member* s1 = MemberFactory::createMember("student", "Saad", 1);
    lib.addMember(s1);

    int choice, copies;
    string isbn, title, author, category, keyword, name, type;

    

    do {
        cout << "\n--- LIBRARY MENU ---\n";
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Show All Books" << endl;
        cout << "5. Issue Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. Add Member" << endl;
        cout << "8. Show All Members" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter choice: ";
        choice = getValidInt();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice < 0 || choice > 8) {
            cout << "Invalid choice! Try again." << endl;
            continue;
        }

        switch (choice) {

        case 1:
            cout << "Enter ISBN: ";
            isbn = getValidString();

            cout << "Enter Title: ";
            title = getValidString();

            cout << "Enter Author: ";
            author = getValidString();

            cout << "Enter Category: ";
            category = getValidString();

            cout << "Enter Copies: ";
            copies = getValidInt();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            lib.addBook(new Book(isbn, title, author, category, copies));
            cout << "Book added!\n";
            break;

        case 2:
            cout << "Enter ISBN to remove: ";
            isbn = getValidString();
            lib.removeBook(isbn);
            break;

        case 3:
            cout << "Enter ISBN or Title: ";
            keyword = getValidString();
            lib.searchBook(keyword);
            break;

        case 4:
            lib.showAllBooks();
            break;

        case 5:
            cout << "Enter ISBN: ";
            isbn = getValidString();
            lib.issueBook(isbn, s1);
            break;

        case 6:
            cout << "Enter ISBN: ";
            isbn = getValidString();
            lib.returnBook(isbn, s1);
            break;

        case 7:
            cout << "Enter Name: ";
            name = getValidString();

            cout << "Enter Type (student/faculty/external): ";
            type = getValidString();

            int id;
            cout << "Enter ID: ";
            id = getValidInt();

            m = MemberFactory::createMember(type, name, id);
            lib.addMember(m);

            cout << "Member added!\n";
            break;

        case 8:
            lib.showAllMembers();
            break;

        case 0:
            lib.saveBooks();
            lib.saveMembers();
            cout << "Data saved. Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}