#include <stdexcept>

#include <gtest/gtest.h>

#include "Day.h"

TEST(DayConstruction, StoresAValidDate) {
    const Day day(2024, 2, 29);

    EXPECT_EQ(day.getYear(), 2024);
    EXPECT_EQ(day.getMonth(), 2);
    EXPECT_EQ(day.getDate(), 29);
}

TEST(DayConstruction, RejectsInvalidMonth) {
    EXPECT_THROW(Day(2024, 0, 10), std::invalid_argument);
    EXPECT_THROW(Day(2024, 13, 10), std::invalid_argument);
}

TEST(DayConstruction, RejectsInvalidDate) {
    EXPECT_THROW(Day(2024, 2, 30), std::invalid_argument);
    EXPECT_THROW(Day(2023, 2, 29), std::invalid_argument);
}

TEST(DayDifference, HandlesSameAndAdjacentDates) {
    const Day first(2025, 1, 1);
    const Day second(2025, 1, 10);

    EXPECT_EQ(first.daysFrom(first), 0);
    EXPECT_EQ(second.daysFrom(first), 9);
    EXPECT_EQ(first.daysFrom(second), -9);
    EXPECT_EQ(Day(2025, 1, 2).daysFrom(first), 1);
}

TEST(DayDifference, HandlesLeapAndYearBoundaries) {
    EXPECT_EQ(Day(2024, 3, 1).daysFrom(Day(2024, 2, 28)), 2);
    EXPECT_EQ(Day(2024, 1, 1).daysFrom(Day(2023, 1, 1)), 365);
    EXPECT_EQ(Day(2025, 1, 1).daysFrom(Day(2024, 1, 1)), 366);
    EXPECT_EQ(Day(2025, 1, 1).daysFrom(Day(2024, 12, 31)), 1);
}

TEST(DayArithmetic, ReturnsANewDateForForwardOffsets) {
    const Day start(2024, 1, 31);
    const Day result = start.plusDays(1);

    EXPECT_EQ(result.getYear(), 2024);
    EXPECT_EQ(result.getMonth(), 2);
    EXPECT_EQ(result.getDate(), 1);
    EXPECT_EQ(start.getDate(), 31);
}

TEST(DayArithmetic, ReturnsANewDateForBackwardOffsets) {
    const Day start(2024, 3, 1);
    const Day result = start.plusDays(-2);

    EXPECT_EQ(result.getMonth(), 2);
    EXPECT_EQ(result.getDate(), 28);
    EXPECT_EQ(start.getMonth(), 3);
}

TEST(DayArithmetic, HandlesLargeOffsets) {
    EXPECT_EQ(Day(2023, 12, 1).plusDays(31).getDate(), 1);
    EXPECT_EQ(Day(2023, 12, 1).plusDays(31).getMonth(), 1);
    EXPECT_EQ(Day(2024, 1, 1).plusDays(366).getYear(), 2025);
    EXPECT_EQ(Day(2024, 1, 1).plusDays(366).getDate(), 1);
}

TEST(DayOrdering, OrdersChronologically) {
    const Day earlier(2024, 12, 31);
    const Day later(2025, 1, 1);

    EXPECT_TRUE(earlier < later);
    EXPECT_FALSE(later < earlier);
    EXPECT_FALSE(earlier < earlier);
    EXPECT_FALSE(Day(2025, 1, 1) < later);
}
