#include "Person.h"

#include <stdexcept>
#include <utility>

Person::Person(std::string name, const Day& birthday)
    : name_(std::move(name)), birthday_(birthday) {
    // TODO: reject an empty name.
}

std::string Person::getName() const {
    return name_;
}

Day Person::getBirthday() const {
    return birthday_;
}

void Person::markBirthdayPassed() {
    // TODO: replace the birthday with its next-year value.
}
