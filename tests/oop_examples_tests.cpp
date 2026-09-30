#include "book/inheritance/Employee.h"
#include "book/inheritance/Manager.h"
#include "intro/NumberGuessGame.h"
#include "intro/Point.h"
#include "polymorphism/states/State.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

TEST(PointTest, StoresCoordinates)
{
    const Point point(3, 4);

    EXPECT_EQ(point.getX(), 3);
    EXPECT_EQ(point.getY(), 4);
}

TEST(EmployeeTest, StartsWithDefaultSalary)
{
    const Employee employee("Ajay");

    EXPECT_EQ(employee.getName(), "Ajay");
    EXPECT_DOUBLE_EQ(employee.getSalary(), 50000.0);
}

TEST(EmployeeTest, SalaryCanBeChanged)
{
    Employee employee("Ajay");
    employee.setSalary(65000.0);

    EXPECT_DOUBLE_EQ(employee.getSalary(), 65000.0);
}

TEST(ManagerTest, AddsBonusThroughOverriddenSalary)
{
    Manager manager("Vijay");

    EXPECT_DOUBLE_EQ(manager.getSalary(), 60000.0);
    manager.setBonus(20000.0);
    EXPECT_DOUBLE_EQ(manager.getSalary(), 70000.0);
}

TEST(ManagerTest, WorksThroughEmployeeReference)
{
    Manager manager("Vijay");
    Employee& employeeReference = manager;

    EXPECT_DOUBLE_EQ(employeeReference.getSalary(), 60000.0);
}

TEST(NumberGuessGameTest, GivesUsefulHints)
{
    const NumberGuessGame game(50);

    EXPECT_EQ(game.hint(20), "Too low!");
    EXPECT_EQ(game.hint(80), "Too high!");
    EXPECT_EQ(game.hint(50), "Correct!");
    EXPECT_TRUE(game.isCorrect(50));
    EXPECT_FALSE(game.isCorrect(49));
}

TEST(StateTest, SortsByPopulationWithNaturalOrdering)
{
    std::vector<State> states{
        State("Goa", 158300, 3702),
        State("Maharashtra", 127528000, 307713),
        State("Karnataka", 68115000, 191791),
    };

    std::sort(states.begin(), states.end());

    EXPECT_EQ(states[0].getName(), "Goa");
    EXPECT_EQ(states[1].getName(), "Karnataka");
    EXPECT_EQ(states[2].getName(), "Maharashtra");
}

TEST(StateTest, SupportsCustomAreaOrdering)
{
    std::vector<State> states{
        State("Goa", 158300, 3702),
        State("Maharashtra", 127528000, 307713),
        State("Karnataka", 68115000, 191791),
    };

    std::sort(states.begin(), states.end(), [](const State& left, const State& right) {
        return left.getArea() > right.getArea();
    });

    EXPECT_EQ(states[0].getName(), "Maharashtra");
    EXPECT_EQ(states[1].getName(), "Karnataka");
    EXPECT_EQ(states[2].getName(), "Goa");
}
