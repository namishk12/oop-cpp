#include "book/inheritance/Employee.h"

Employee::Employee(std::string name)
    : name(name), salary(50000.0)
{
}

void Employee::setSalary(double newSalary)
{
    salary = newSalary;
}

const std::string& Employee::getName() const noexcept
{
    return name;
}

double Employee::getSalary() const noexcept
{
    return salary;
}
