#pragma once

#include <string>

class State {
public:
    State(std::string name, int population, int area);

    const std::string& getName() const noexcept;
    int getPopulation() const noexcept;
    int getArea() const noexcept;
    bool operator<(const State& other) const noexcept;

private:
    std::string name;
    int population;
    int area;
};
