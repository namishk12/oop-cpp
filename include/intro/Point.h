#pragma once

class Point {
public:
    Point(int x, int y);

    int getX() const noexcept;
    int getY() const noexcept;

private:
    int x;
    int y;
};
