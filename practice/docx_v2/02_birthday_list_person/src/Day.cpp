#include "Day.h"

#include <stdexcept>

bool Day::isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int Day::daysInMonth(int year, int month) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

Day::Day(int year, int month, int date)
    : year_(year), month_(month), date_(date) {
    if (year <= 0 || month < 1 || month > 12 || date < 1 ||
        date > daysInMonth(year, month)) {
        throw std::invalid_argument("invalid date");
    }
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

int Day::serial() const {
    int result = 0;
    for (int year = 1; year < year_; ++year) {
        result += isLeapYear(year) ? 366 : 365;
    }
    for (int month = 1; month < month_; ++month) {
        result += daysInMonth(year_, month);
    }
    return result + date_ - 1;
}

int Day::daysFrom(const Day& other) const {
    return serial() - other.serial();
}

Day Day::plusYears(int years) const {
    const int targetYear = year_ + years;
    int targetDate = date_;
    if (month_ == 2 && date_ == 29 && !isLeapYear(targetYear)) {
        targetDate = 28;
    }
    return Day(targetYear, month_, targetDate);
}
