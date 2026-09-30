#include "polymorphism/states/State.h"

State::State(std::string name, int population, int area)
    : name(name), population(population), area(area)
{
}

const std::string& State::getName() const noexcept
{
    return name;
}

int State::getPopulation() const noexcept
{
    return population;
}

int State::getArea() const noexcept
{
    return area;
}

bool State::operator<(const State& other) const noexcept
{
    return population < other.population;
}
