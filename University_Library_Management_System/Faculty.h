#ifndef FACULTY_H
#define FACULTY_H

#include "Member.h"

class Faculty : public Member {
public:
    Faculty(string n, int i) : Member(n, i) {}

    int getMaxBooks() { return 8; }
    int getDaysLimit() { return 30; }
    double getFinePerDay() { return 0; }
};

#endif