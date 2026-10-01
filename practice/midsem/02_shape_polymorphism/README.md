# Question 2 — Shape Catalogue

## Problem

Implement a small shape catalogue from the supplied UML. `Shape` is an
abstract interface. `Circle` and `Rectangle` are concrete derived classes. A
`ShapeCatalog` owns a collection of shapes and offers aggregate analysis
without knowing which concrete shape types were inserted.

## Contract

- `Circle` requires a strictly positive radius.
- `Rectangle` requires strictly positive width and height.
- Invalid dimensions throw `std::invalid_argument`.
- `area()` and `perimeter()` are `const` and have no side effects.
- `ShapeCatalog::add` takes ownership of a non-null shape.
- `totalArea()` sums through the abstract `Shape` interface.
- `namesByArea()` returns names in ascending area order. Ties are broken by
  name, also ascending.
- Destroying a shape through a `Shape*` must be safe.

## What is being tested

Pure virtual functions, public inheritance, virtual destruction, runtime
dispatch, composition/ownership, `std::sort`, and a comparator lambda or
functor. The client code must not use `dynamic_cast` or inspect concrete types.

## Exam-style deliverables

1. Implement only the `.cpp` files.
2. Add at least four tests for each non-getter public operation.
3. Add one test proving that a catalogue can aggregate different derived types
   through `Shape` pointers.

See [Shape.mmd](docs/Shape.mmd) and the supplied headers.
