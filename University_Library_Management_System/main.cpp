#include "Library.h"
#include "MemberFactory.h"
#include "Validation.h"

int main() {
    Library lib;

    lib.loadBooks();

    // Load test members with mixed types
    Member* m = NULL;
    
    // Students (max 3 books, 14 days, 5 fine per day)
    Member* s1 = MemberFactory::createMember("student", "Saad", 1);
    lib.addMember(s1);
    Member* s2 = MemberFactory::createMember("student", "Ahmed", 2);
    lib.addMember(s2);
    Member* s3 = MemberFactory::createMember("student", "Fatima", 3);
    lib.addMember(s3);
    Member* s4 = MemberFactory::createMember("student", "Hassan", 4);
    lib.addMember(s4);
    Member* s5 = MemberFactory::createMember("student", "Aisha", 5);
    lib.addMember(s5);
    Member* s6 = MemberFactory::createMember("student", "Ali", 7);
    lib.addMember(s6);
    Member* s7 = MemberFactory::createMember("student", "Zainab", 8);
    lib.addMember(s7);
    Member* s8 = MemberFactory::createMember("student", "Bilal", 9);
    lib.addMember(s8);
    Member* s9 = MemberFactory::createMember("student", "Mariam", 11);
    lib.addMember(s9);
    Member* s10 = MemberFactory::createMember("student", "Karim", 12);
    lib.addMember(s10);
    
    // Faculty (max 8 books, 30 days, no fine)
    Member* f1 = MemberFactory::createMember("faculty", "Dr. Khan", 6);
    lib.addMember(f1);
    Member* f2 = MemberFactory::createMember("faculty", "Prof. Ahmed", 10);
    lib.addMember(f2);
    
    // External (max 2 books, 7 days, 5 fine per day)
    Member* e1 = MemberFactory::createMember("external", "Amina", 13);
    lib.addMember(e1);
    Member* e2 = MemberFactory::createMember("external", "Omar", 14);
    lib.addMember(e2);
    Member* e3 = MemberFactory::createMember("external", "Noor", 15);
    lib.addMember(e3);
    Member* e4 = MemberFactory::createMember("external", "Yasmine", 16);
    lib.addMember(e4);
    Member* e5 = MemberFactory::createMember("external", "Rayan", 17);
    lib.addMember(e5);

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