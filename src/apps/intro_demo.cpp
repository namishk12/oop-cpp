#include "intro/Point.h"

#include <iostream>
#include <string>

int main()
{
    const std::string first = "BITSGoa";
    const std::string second = "BI" + std::string("TS");
    const std::string prefix = first.substr(0, 4);

    std::cout << "first: " << first << ", second: " << second
              << ", prefix: " << prefix << '\n';
    std::cout << "second == prefix: " << (second == prefix) << '\n';

    const Point point(3, 4);
    std::cout << "Point(" << point.getX() << ", " << point.getY() << ")\n";
    return 0;
}
