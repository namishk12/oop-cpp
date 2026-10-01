# Design Notes

Compare this folder with Question 1 after writing tests:

1. Which class owns the name and birthday invariant now?
2. Can a `BirthdayList` accidentally make its two collections different
   lengths?
3. Which class should implement `markBirthdayPassed`?
4. Does returning a `Person` by value or by const reference change coupling?
5. What additional attributes could be added to `Person` without making
   `BirthdayList` less cohesive?

There is intentionally no model discussion in the starter folder.
