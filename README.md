# OOP Examples in C++

An independent C++17 learning repository based on the structure of the linked
object-oriented programming reference material. It contains:

- Introductory classes: `Point` and a deterministic/testable number-guessing game.
- Inheritance: `Employee` and `Manager` with virtual dispatch.
- OOAD number duel: players, profiles, guesses, history, feedback, and game rules.
- Polymorphism/sorting: `State` with natural population ordering and custom area ordering.
- UPI wallet: balance constraints, transaction history, and analysis methods.
- Mermaid class diagrams under `docs/diagrams/`.

The wallet uses `std::time_t` timestamps generated with `std::time(nullptr)`. Invalid
amounts and overdrafts throw `std::invalid_argument` before changing wallet state.

## Build and test

CMake downloads GoogleTest through `FetchContent` during configuration. Build and run:

```text
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The interactive examples are built as `intro_demo`, `number_guess_game`,
`employee_tester`, `states_tester`, and `number_duel_app`.

## Layout

```text
include/       public class headers
src/           class implementations and example applications
tests/         GoogleTest suites
docs/diagrams/ Mermaid UML diagrams
```

The code is written as original C++ practice material; it does not copy the Java
source layout or require Gradle.
