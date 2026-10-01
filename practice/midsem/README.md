# C++ Lab Midsem Practice Pack

This pack is based on the attached lab slides. It is intentionally written in
the format likely to appear in the lab exam:

- the UML and public headers are supplied;
- most work is in the `.cpp` files;
- tests are written with GoogleTest;
- CMake is supplied;
- implementation must be developed with TDD;
- no `std::chrono` is needed. The wallet question uses `std::time_t` and
  `std::time(nullptr)` only.

The starter `.cpp` files are incomplete on purpose. A fresh run should be
treated as the red phase of TDD. Do not read the tests as a replacement for the
specification: use the question statement, UML, contracts, and tests together.

## Questions

| Project | Main topics | Suggested time |
| --- | --- | ---: |
| [01 Day Contract](01_day_contract/README.md) | encapsulation, immutability, date arithmetic, contracts | 45 min |
| [02 Shape Polymorphism](02_shape_polymorphism/README.md) | abstract interfaces, inheritance, virtual dispatch, sorting/lambdas | 45 min |
| [03 Wallet Audit](03_wallet_audit/README.md) | aggregation, exceptions, audit trail, `time_t`, analysis | 45 min |
| [04 Number Duel](04_number_duel/README.md) | OOAD, state, composition, turn rules, use-case thinking | 60 min |

## TDD protocol to practise

1. Read the UML and write down each class responsibility.
2. Run one test or one test group before changing code. Record the failure.
3. Implement the smallest behavior in the corresponding `.cpp` file.
4. Run the focused test, then the complete target.
5. Refactor only after the tests are green.
6. Make a small Git commit after each meaningful red-green-refactor cycle.

Useful commit sequence:

```text
test: specify constructor contract
feat: implement constructor contract
test: cover boundary arithmetic
feat: implement boundary arithmetic
refactor: extract private helper
```

## Build

From the repository root:

```text
cmake -S practice/midsem -B build-midsem
cmake --build build-midsem
ctest --test-dir build-midsem --output-on-failure
```

The tests are expected to fail before you implement the TODOs. In an actual
midsem, the examiner may provide a different test skeleton, so do not hard-code
only the visible examples.
