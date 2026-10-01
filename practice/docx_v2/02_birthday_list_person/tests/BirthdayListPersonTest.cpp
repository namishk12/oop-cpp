#include <stdexcept>

#include <gtest/gtest.h>

#include "BirthdayList.h"
#include "Person.h"

TEST(Person, OwnsNameAndBirthday) {
    const Person person("Asha", Day(2000, 8, 17));

    EXPECT_EQ(person.getName(), "Asha");
    EXPECT_EQ(person.getBirthday().getMonth(), 8);
    EXPECT_EQ(person.getBirthday().getDate(), 17);
}

TEST(Person, RejectsAnEmptyName) {
    EXPECT_THROW(Person("", Day(2000, 8, 17)), std::invalid_argument);
}

TEST(Person, AdvancesItsOwnBirthday) {
    Person person("Asha", Day(2000, 8, 17));

    person.markBirthdayPassed();

    EXPECT_EQ(person.getBirthday().getYear(), 2001);
    EXPECT_EQ(person.getBirthday().getMonth(), 8);
    EXPECT_EQ(person.getBirthday().getDate(), 17);
}

TEST(BirthdayList, AddsPersonObjects) {
    BirthdayList list;
    list.addPerson(Person("Asha", Day(2000, 8, 17)));

    EXPECT_EQ(list.size(), 1U);
    EXPECT_EQ(list.personFor("Asha").getBirthday().getDate(), 17);
}

TEST(BirthdayList, RejectsDuplicateNames) {
    BirthdayList list;
    list.addPerson(Person("Asha", Day(2000, 8, 17)));

    EXPECT_THROW(list.addPerson(Person("Asha", Day(2001, 9, 18))),
                 std::invalid_argument);
}

TEST(BirthdayList, RetrievesABirthdayByName) {
    BirthdayList list;
    list.addPerson(Person("Asha", Day(2000, 8, 17)));

    EXPECT_EQ(list.birthdayFor("Asha").getYear(), 2000);
    EXPECT_EQ(list.birthdayFor("Asha").getMonth(), 8);
    EXPECT_EQ(list.birthdayFor("Asha").getDate(), 17);
}

TEST(BirthdayList, RejectsMissingNames) {
    const BirthdayList list;

    EXPECT_THROW(list.personFor("Unknown"), std::invalid_argument);
    EXPECT_THROW(list.birthdayFor("Unknown"), std::invalid_argument);
}

TEST(BirthdayList, FindsTheNearestUpcomingBirthday) {
    BirthdayList list;
    list.addPerson(Person("Far", Day(2000, 12, 31)));
    list.addPerson(Person("Near", Day(2000, 6, 20)));

    EXPECT_EQ(list.daysUntilNextBirthday(Day(2025, 6, 15)), 5);
}

TEST(BirthdayList, DelegatesBirthdayUpdatesToPerson) {
    BirthdayList list;
    list.addPerson(Person("Asha", Day(2000, 8, 17)));

    list.markBirthdayPassed("Asha");

    EXPECT_EQ(list.birthdayFor("Asha").getYear(), 2001);
}

TEST(BirthdayList, RejectsAnEmptyNextBirthdayQuery) {
    const BirthdayList list;

    EXPECT_THROW(list.daysUntilNextBirthday(Day(2025, 6, 15)), std::logic_error);
}
