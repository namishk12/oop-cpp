#pragma once

#include "book/inheritance/Employee.h"

class Manager : public Employee {
public:
    explicit Manager(std::string name);

    void setBonus(double bonus);
    double getSalary() const noexcept override;

private:
    double bonus;
};
