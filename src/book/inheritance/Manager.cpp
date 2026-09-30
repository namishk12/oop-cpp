#include "book/inheritance/Manager.h"

Manager::Manager(std::string name)
    : Employee(name), bonus(10000.0)
{
}

void Manager::setBonus(double newBonus)
{
    bonus = newBonus;
}

double Manager::getSalary() const noexcept
{
    return bonus + Employee::getSalary();
}
