# UPI Wallet (C++)

This project implements the three classes from the lab specification:

- `Wallet` maintains a non-negative balance and an append-only transaction audit trail.
- `Transaction` is an immutable credit/debit record.
- `WalletAnalyzer` calculates credits, debits, and inclusive date-range expenditure.

Amounts must be greater than zero. Invalid amounts and overdrafts throw
`std::invalid_argument` before changing wallet state. The initial balance is not
recorded as a transfer; only calls to `addMoney` and `deductMoney` create audit entries.

Transactions use `std::time_t` timestamps generated with `std::time(nullptr)`, avoiding
the heavier `chrono` library while retaining real time values for date-range analysis.

The implementation uses C++17, CMake, and a dependency-free test executable.

Run the tests with:

```text
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
