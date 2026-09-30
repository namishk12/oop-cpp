#include "polymorphism/states/State.h"

#include <algorithm>
#include <iostream>
#include <vector>

void printStates(const std::vector<State>& states)
{
    for (const State& state : states) {
        std::cout << state.getName() << '\t';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<State> states{
        State("Goa", 158300, 3702),
        State("Maharashtra", 127528000, 307713),
        State("Karnataka", 68115000, 191791),
    };

    std::sort(states.begin(), states.end());
    printStates(states);

    std::sort(states.begin(), states.end(), [](const State& left, const State& right) {
        return left.getArea() > right.getArea();
    });
    printStates(states);
    return 0;
}
