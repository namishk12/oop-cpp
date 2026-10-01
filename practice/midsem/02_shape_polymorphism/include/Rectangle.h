#ifndef MIDSEM_RECTANGLE_H
#define MIDSEM_RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
private:
    double width_;
    double height_;

public:
    Rectangle(double width, double height);

    double area() const override;
    double perimeter() const override;
    std::string name() const override;
};

#endif
