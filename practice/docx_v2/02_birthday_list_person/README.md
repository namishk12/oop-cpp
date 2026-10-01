# Question 2 Birthday List Using a Person Class

Refactor the previous question so that `BirthdayList` stores `Person` objects
instead of parallel name and birthday collections. The list must still add a
person, retrieve a birthday by name, find the nearest next birthday, and mark a
birthday as passed.

## Practice contract

- `Person` owns its name and birthday and exposes const accessors.
- Names must be non-empty and unique inside a `BirthdayList`.
- A missing name throws `std::invalid_argument`.
- An empty list has no next birthday and causes
  `daysUntilNextBirthday` to throw `std::logic_error`.
- `Person::markBirthdayPassed` advances the stored birthday by one year.
- The year in a stored `Day` is the birth year; next-birthday comparison uses
  month and date relative to the supplied `today`.
- `Day` is supplied support code. Treat it as a dependency, not the main
  implementation target.

## Discussion and TDD

Start with tests for the same behavior as Question 1, then add tests proving
that the `Person` object owns the relationship between a name and a birthday.
Compare this design with Question 1 in `docs/design_notes.md`: data ownership,
searching, mutation, cohesion, coupling, extensibility, and testability.

See [BirthdayListPerson.mmd](docs/BirthdayListPerson.mmd).
