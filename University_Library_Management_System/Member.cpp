#include "Member.h"

    Member::Member(string n, int i) {
        name = n;
        id = i;
    }

    string Member::getName(){
        return name;
    }
    int Member::getID(){
        return id;
    }