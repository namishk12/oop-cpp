# Question 4 — Number Duel

## Problem

Implement the core domain model for a two-player number duel. Each player owns
a secret target from 1 to 100. Players alternate guesses. A guess is evaluated
as too low, too high, or a direct hit. The first direct hit ends the game and
awards the winner `100 - number_of_guesses` points.

This is a domain-model question: do not put input/output loops in the classes.
The use-case flow is represented by `NumberDuelGame::submitGuess`.

## Contract

- Player names must not be empty.
- Targets and guesses must be in `[1, 100]`.
- Invalid guesses throw `std::invalid_argument` and do not increment attempts.
- Every valid guess increments the active player's attempt count exactly once.
- A non-winning turn switches the active player.
- A direct hit ends the game and does not switch the winner away.
- Submitting after game over throws `std::logic_error`.
- A game has exactly one winner after game over and no winner before it.
- `Player::score()` is zero before a win and otherwise follows the point rule;
  it must never be negative.

## What is being tested

Candidate classes and responsibilities, aggregation, state transitions, public
inheritance-style interfaces from the earlier slides, invariants, preconditions,
postconditions, and a testable separation between domain logic and UI.

## Exam-style deliverables

1. Implement only the `.cpp` files.
2. Add at least four tests for each non-getter public operation.
3. Write a short use-case note for `Submit Guess` and identify its exceptional
   variations.
4. Make a small commit after each TDD cycle.

See [NumberDuel.mmd](docs/NumberDuel.mmd) and the supplied headers.
