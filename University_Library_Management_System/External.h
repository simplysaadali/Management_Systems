#ifndef EXTERNAL_H
#define EXTERNAL_H

#include "Member.h"

class External : public Member {
private:
    int renewalYears; // Track years for renewal

public:
    External(string n, int i) : Member(n, i) {
        renewalYears = 1; // Renewed yearly
    }

    int getMaxBooks(){
        return 2;
    }
    int getDaysLimit(){
        return 7;
    }
    double getFinePerDay(){
        return 5;
    }
    
    int getRenewalYears(){
        return renewalYears;
    }
};

#endif