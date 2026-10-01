#ifndef MIDSEM_SHAPE_H
#define MIDSEM_SHAPE_H

#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
};

#endif
