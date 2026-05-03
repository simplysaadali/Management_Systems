#include "Validation.h"

int getValidInt() {
    int x;

    while (true) {
        cin >> x;

        if (cin.fail()) {
            cout << "Invalid input! Enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return x;
        }
    }
}

string getValidString() {
    string s;

    while (true) {
        getline(cin, s);

        if (s.find_first_not_of(" \t") == string::npos) {
            cout << "Input cannot be empty. Try again: ";
        } else {
            return s;
        }
    }
}