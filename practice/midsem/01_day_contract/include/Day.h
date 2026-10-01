#ifndef MIDSEM_DAY_H
#define MIDSEM_DAY_H

class Day {
private:
    int year_;
    int month_;
    int date_;

    static bool isLeapYear(int year);
    static int daysInMonth(int year, int month);
    int serial() const;
    static Day fromSerial(int serial);

public:
    Day(int year, int month, int date);

    int getYear() const;
    int getMonth() const;
    int getDate() const;

    int daysFrom(const Day& other) const;
    Day plusDays(int n) const;
    bool operator<(const Day& other) const;
};

#endif
