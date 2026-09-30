#include "intro/Point.h"

Point::Point(int x, int y)
    : x(x), y(y)
{
}

int Point::getX() const noexcept
{
    return x;
}

int Point::getY() const noexcept
{
    return y;
}
