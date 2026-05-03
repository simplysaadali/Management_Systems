#ifndef LOGGER_H
#define LOGGER_H

// used to get or print the value of the function, like the book is issued or returned and etc...
#include <iostream>
using namespace std;

class Logger {
private:
// taking pointer due o singeleton structure of the program accoridng to th e requirement...
// only one is hared in the whole program...
    static Logger* instance;

    // it is private so that nobody can create the objec of this class Logger...
    Logger() {}

public:
// creating a function so that logger sould be accessed...
    static Logger* getInstance();

    // this function prints the msg of wha is done...
    void log(string msg);
};

#endif