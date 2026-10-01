# Question 1 — Immutable `Day`

## Problem

Implement the `Day` class shown in the supplied header and UML. `Day` models a
valid Gregorian calendar date and deliberately contains no time-zone or clock
behavior. Its public interface must remain stable even if its private date
representation changes later.

## Contract

- `year` must be positive.
- `month` must be in `[1, 12]`.
- `date` must be valid for the month, including Gregorian leap-year rules.
- An invalid constructor argument throws `std::invalid_argument` and creates no
  usable invalid object.
- `daysFrom(other)` returns `this - other` in whole days; the sign matters.
- `plusDays(n)` returns a new `Day`; it must not modify the receiver.
- `operator<` orders dates chronologically.
- Do not expose public data members or mutators.

## What is being tested

Leap years, month/year boundaries, negative offsets, symmetry of date
differences, const-correct accessors, immutability, and strict encapsulation.

## Exam-style deliverables

1. Implement only `src/Day.cpp` unless the supplied header cannot compile.
2. Add at least four tests for each non-getter operation.
3. Add one UML or written note identifying the constructor preconditions,
   method postconditions, and class invariant.

See [Day.mmd](docs/Day.mmd) and the supplied [Day.h](include/Day.h).
