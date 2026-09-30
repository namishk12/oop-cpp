#include "book/inheritance/Employee.h"
#include "book/inheritance/Manager.h"

#include <iostream>

int main()
{
    Employee employee("Ajay");
    Manager manager("Vijay");
    Employee& polymorphicManager = manager;

    std::cout << employee.getName() << " - " << employee.getSalary() << '\n';
    std::cout << manager.getName() << " - " << manager.getSalary() << '\n';
    std::cout << polymorphicManager.getName() << " - "
              << polymorphicManager.getSalary() << '\n';
    return 0;
}
