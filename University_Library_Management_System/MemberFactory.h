#ifndef FACTORY_H
#define FACTORY_H

#include "student.h"
#include "faculty.h"
#include "external.h"

class MemberFactory {
public:
    static Member* createMember(string type, string name, int id) {
        if (type == "student")
            return new Student(name, id);
        else if (type == "faculty")
            return new Faculty(name, id);
        else
            return new External(name, id);
    }
};

#endif