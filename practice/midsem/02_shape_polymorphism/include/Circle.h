#ifndef MIDSEM_CIRCLE_H
#define MIDSEM_CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
private:
    double radius_;

public:
    explicit Circle(double radius);

    double area() const override;
    double perimeter() const override;
    std::string name() const override;
};

#endif
