#ifndef DOCX_V2_PERSON_BIRTHDAY_LIST_H
#define DOCX_V2_PERSON_BIRTHDAY_LIST_H

#include <cstddef>
#include <string>
#include <vector>

#include "Person.h"

class BirthdayList {
private:
    std::vector<Person> people_;

    std::size_t findIndex(const std::string& name) const;
    Day nextOccurrence(const Day& birthday, const Day& today) const;

public:
    void addPerson(const Person& person);
    Person personFor(const std::string& name) const;
    Day birthdayFor(const std::string& name) const;
    int daysUntilNextBirthday(const Day& today) const;
    void markBirthdayPassed(const std::string& name);
    std::size_t size() const;
};

#endif
