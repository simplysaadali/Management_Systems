#ifndef STUDENT_H
#define STUDENT_H

#include "Member.h"

class Student : public Member {
public:
    Student(string n, int i) : Member(n, i) {}

    int getMaxBooks() { return 3; }
    int getDaysLimit() { return 14; }
    double getFinePerDay() { return 5; }
};

#endif