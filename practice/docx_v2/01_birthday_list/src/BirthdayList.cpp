#include "BirthdayList.h"

#include <stdexcept>

std::size_t BirthdayList::findIndex(const std::string& name) const {
    (void)name;
    // TODO: return the matching index or throw std::invalid_argument.
    return 0;
}

Day BirthdayList::nextOccurrence(const Day& birthday, const Day& today) const {
    (void)birthday;
    (void)today;
    // TODO: create this year's occurrence and roll to next year when needed.
    return Day(2000, 1, 1);
}

void BirthdayList::addBirthday(const std::string& name, const Day& birthday) {
    (void)name;
    (void)birthday;
    // TODO: validate the name, reject duplicates, and keep both vectors aligned.
}

Day BirthdayList::birthdayFor(const std::string& name) const {
    (void)name;
    // TODO: return the stored birthday for the requested name.
    return Day(2000, 1, 1);
}

int BirthdayList::daysUntilNextBirthday(const Day& today) const {
    (void)today;
    // TODO: find the minimum non-negative distance across all birthdays.
    return 0;
}

void BirthdayList::markBirthdayPassed(const std::string& name) {
    (void)name;
    // TODO: advance only the matching stored birthday by one year.
}

std::size_t BirthdayList::size() const {
    return names_.size();
}
