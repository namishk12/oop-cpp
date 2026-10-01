#include <stdexcept>

#include <gtest/gtest.h>

#include "BirthdayList.h"

TEST(BirthdayList, StartsEmpty) {
    const BirthdayList list;

    EXPECT_EQ(list.size(), 0U);
}

TEST(BirthdayList, AddsAndRetrievesABirthday) {
    BirthdayList list;
    list.addBirthday("Asha", Day(2000, 8, 17));

    EXPECT_EQ(list.size(), 1U);
    EXPECT_EQ(list.birthdayFor("Asha").getMonth(), 8);
    EXPECT_EQ(list.birthdayFor("Asha").getDate(), 17);
}

TEST(BirthdayList, RejectsEmptyAndDuplicateNames) {
    BirthdayList list;
    EXPECT_THROW(list.addBirthday("", Day(2000, 8, 17)), std::invalid_argument);

    list.addBirthday("Asha", Day(2000, 8, 17));
    EXPECT_THROW(list.addBirthday("Asha", Day(2001, 9, 18)), std::invalid_argument);
}

TEST(BirthdayList, RejectsMissingNames) {
    BirthdayList list;

    EXPECT_THROW(list.birthdayFor("Unknown"), std::invalid_argument);
    EXPECT_THROW(list.markBirthdayPassed("Unknown"), std::invalid_argument);
}

TEST(BirthdayList, FindsTheNearestUpcomingBirthday) {
    BirthdayList list;
    list.addBirthday("Far", Day(2000, 12, 31));
    list.addBirthday("Near", Day(2000, 6, 20));
    list.addBirthday("PastThisYear", Day(2000, 6, 10));

    EXPECT_EQ(list.daysUntilNextBirthday(Day(2025, 6, 15)), 5);
}

TEST(BirthdayList, HandlesTodayAsZeroDaysAway) {
    BirthdayList list;
    list.addBirthday("Asha", Day(2000, 6, 15));

    EXPECT_EQ(list.daysUntilNextBirthday(Day(2025, 6, 15)), 0);
}

TEST(BirthdayList, RejectsNextBirthdayQueryForAnEmptyList) {
    const BirthdayList list;

    EXPECT_THROW(list.daysUntilNextBirthday(Day(2025, 6, 15)), std::logic_error);
}

TEST(BirthdayList, AdvancesOnlyTheRequestedBirthday) {
    BirthdayList list;
    list.addBirthday("Asha", Day(2000, 8, 17));
    list.addBirthday("Bala", Day(2001, 9, 18));

    list.markBirthdayPassed("Asha");

    EXPECT_EQ(list.birthdayFor("Asha").getYear(), 2001);
    EXPECT_EQ(list.birthdayFor("Bala").getYear(), 2001);
}
