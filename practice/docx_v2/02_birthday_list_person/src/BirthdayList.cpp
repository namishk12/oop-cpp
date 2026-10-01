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
    // TODO: calculate this year's or next year's occurrence.
    return Day(2000, 1, 1);
}

void BirthdayList::addPerson(const Person& person) {
    (void)person;
    // TODO: reject duplicate names and store the Person.
}

Person BirthdayList::personFor(const std::string& name) const {
    (void)name;
    // TODO: return the requested Person.
    return Person("placeholder", Day(2000, 1, 1));
}

Day BirthdayList::birthdayFor(const std::string& name) const {
    (void)name;
    // TODO: delegate the lookup to the matching Person.
    return Day(2000, 1, 1);
}

int BirthdayList::daysUntilNextBirthday(const Day& today) const {
    (void)today;
    // TODO: find the minimum non-negative distance across all people.
    return 0;
}

void BirthdayList::markBirthdayPassed(const std::string& name) {
    (void)name;
    // TODO: delegate the mutation to the matching Person.
}

std::size_t BirthdayList::size() const {
    return people_.size();
}
