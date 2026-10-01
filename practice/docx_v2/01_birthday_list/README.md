# Question 1 Birthday List

Implement `BirthdayList` using separate name and birthday collections. A
`Day` value type is supplied as support code. The list must support adding a
person, looking up a birthday by name, finding the smallest number of days
until any next birthday, and marking a birthday as passed.

## Practice contract

- Names must be non-empty and unique.
- A missing name throws `std::invalid_argument`.
- An empty list has no next birthday and causes
  `daysUntilNextBirthday` to throw `std::logic_error`.
- The year in a stored `Day` is the birth year; comparisons for the next
  birthday use only month and date relative to the supplied `today`.
- `markBirthdayPassed` advances that stored birthday by one year. The supplied
  `Day` handles February 29 in a non-leap year by using February 28.
- `Day` is provided here to make the folder buildable. Treat it as an
  examiner-provided dependency and normally do not modify it.

## TDD and design work

Write tests first for duplicate names, missing names, empty lists, dates before
and after today, year boundaries, and updating a passed birthday. Then
implement `BirthdayList.cpp`. Discuss in `docs/design_notes.md` why parallel
collections create more coupling than the Person-object design in Question 2.

See [BirthdayList.mmd](docs/BirthdayList.mmd).
