#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <limits>
using namespace std;

// Integer validation
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



// String validation (non-empty)
  string getValidString() {
    string s;

    while (true) {
        getline(cin, s);

        // using a unction that can't tak any empty input...
        if (s.find_first_not_of(" \t") == string::npos) {
            cout << "Input cannot be empty. Try again: ";
        } else {
            return s;
        }
    }
}

#endif