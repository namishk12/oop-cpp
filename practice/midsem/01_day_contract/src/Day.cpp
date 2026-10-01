#include "Day.h"

Day::Day(int year, int month, int date)
    : year_(year), month_(month), date_(date) {
    // TODO: enforce the constructor contract.
}

int Day::getYear() const {
    return year_;
}

int Day::getMonth() const {
    return month_;
}

int Day::getDate() const {
    return date_;
}

bool Day::isLeapYear(int year) {
    (void)year;
    // TODO: implement Gregorian leap-year rules.
    return false;
}

int Day::daysInMonth(int year, int month) {
    (void)year;
    (void)month;
    // TODO: return the correct number of days in the month.
    return 0;
}

int Day::serial() const {
    // TODO: convert this date to a monotonically increasing day number.
    return 0;
}

Day Day::fromSerial(int serial) {
    (void)serial;
    // TODO: convert a day number back to a valid Day.
    return Day(1, 1, 1);
}

int Day::daysFrom(const Day& other) const {
    (void)other;
    // TODO: return this->serial() - other.serial().
    return 0;
}

Day Day::plusDays(int n) const {
    (void)n;
    // TODO: return a new date without modifying *this.
    return *this;
}

bool Day::operator<(const Day& other) const {
    (void)other;
    // TODO: implement chronological ordering.
    return false;
}
