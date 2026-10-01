#ifndef DOCX_V2_DAY_H
#define DOCX_V2_DAY_H

class Day {
private:
    int year_;
    int month_;
    int date_;

    static bool isLeapYear(int year);
    static int daysInMonth(int year, int month);
    int serial() const;

public:
    Day(int year, int month, int date);

    int getYear() const;
    int getMonth() const;
    int getDate() const;
    int daysFrom(const Day& other) const;
    Day plusYears(int years) const;
};

#endif
