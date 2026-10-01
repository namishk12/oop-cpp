#ifndef DOCX_V2_BIRTHDAY_LIST_H
#define DOCX_V2_BIRTHDAY_LIST_H

#include <cstddef>
#include <string>
#include <vector>

#include "Day.h"

class BirthdayList {
private:
    std::vector<std::string> names_;
    std::vector<Day> birthdays_;

    std::size_t findIndex(const std::string& name) const;
    Day nextOccurrence(const Day& birthday, const Day& today) const;

public:
    void addBirthday(const std::string& name, const Day& birthday);
    Day birthdayFor(const std::string& name) const;
    int daysUntilNextBirthday(const Day& today) const;
    void markBirthdayPassed(const std::string& name);
    std::size_t size() const;
};

#endif
