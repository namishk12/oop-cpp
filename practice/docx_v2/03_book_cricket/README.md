# Question 3 Book Cricket Simulator

Design and implement a two-innings book-cricket simulator. A page number is
selected for every delivery, and its last digit determines the outcome:

| Last digit | Outcome |
| --- | --- |
| 1, 2, 3, 4, 6 | that many runs |
| 5 | wide; one extra run and no legal-ball count |
| 7, 9 | no effect; one legal ball |
| 0, 8 | out; one legal ball and the innings ends |

Each over has six legal deliveries. The match has two innings, with the
starting batsman chosen by the caller. After both innings, report the winner or
a tie.

## Practice contract

- Page numbers must be non-negative.
- Overs must be positive.
- A wide adds one run but does not consume a legal ball.
- Runs, no-effect deliveries, and outs consume one legal ball.
- An innings ends on an out or after `overs * 6` legal balls.
- Deliveries after an innings is complete throw `std::logic_error`.
- `Match::play` receives deterministic page sequences so the domain model is
  unit-testable. The random page generator and user interaction belong in an
  application layer, not in the tested domain classes.
- For TDD, test the rules before testing the match orchestration.

## Required design work

Before implementation, make a use-case note and CRC cards for the classes you
choose. The supplied skeleton uses `BookCricketRules`, `Innings`, and `Match`,
but you may add a small page-source abstraction if you can justify it.

See [BookCricket.mmd](docs/BookCricket.mmd) and
[use_cases.md](docs/use_cases.md).
