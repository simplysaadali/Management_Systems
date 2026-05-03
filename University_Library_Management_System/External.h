#ifndef EXTERNAL_H
#define EXTERNAL_H

#include "Member.h"

class External : public Member {
public:
    External(string n, int i) : Member(n, i) {}

    int getMaxBooks() { return 2; }
    int getDaysLimit() { return 7; }
    double getFinePerDay() { return 5; }
};

#endif