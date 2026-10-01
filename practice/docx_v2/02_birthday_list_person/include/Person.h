#ifndef DOCX_V2_PERSON_H
#define DOCX_V2_PERSON_H

#include <string>

#include "Day.h"

class Person {
private:
    std::string name_;
    Day birthday_;

public:
    Person(std::string name, const Day& birthday);

    std::string getName() const;
    Day getBirthday() const;
    void markBirthdayPassed();
};

#endif
