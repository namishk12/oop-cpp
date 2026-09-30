#pragma once

#include <string>

class Employee {
public:
    explicit Employee(std::string name);
    virtual ~Employee() = default;

    void setSalary(double salary);
    const std::string& getName() const noexcept;
    virtual double getSalary() const noexcept;

private:
    std::string name;
    double salary;
};
