#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
using namespace std;

class Member {
protected:
    string name;
    int id;

public:
    Member(string n, int i);

    virtual int getMaxBooks() = 0;
    virtual int getDaysLimit() = 0;
    virtual double getFinePerDay() = 0;

    string getName();
    int getID();
};

#endif