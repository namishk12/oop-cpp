# Question 3 — Wallet Audit

## Problem

Implement a small wallet that maintains a balance and an append-only
chronological transaction history. A separate `WalletAnalyzer` reports totals
without taking ownership of the wallet. The UML models an aggregation between
the analyzer and wallet, and composition of transactions inside the wallet.

## Contract

- The wallet identifier must not be empty.
- Opening balance must be non-negative.
- Every transfer amount must be strictly positive.
- `addMoney` increases the balance and appends one credit transaction.
- `deductMoney` requires `amount <= balance`; otherwise it throws
  `std::invalid_argument` and changes nothing.
- Failed operations must not append transactions.
- Transactions are stored in operation order and receive a timestamp from
  `std::time(nullptr)`.
- `totalAmountCredited()` and `totalAmountDebited()` sum only the appropriate
  transaction types.
- `expenditureBetween(start, end)` is inclusive at both endpoints and counts
  only debits. If `start > end`, throw `std::invalid_argument`.
- Do not use `std::chrono`; this exercise intentionally uses `std::time_t`.

## What is being tested

Encapsulation, aggregation versus composition, exception safety, invariants,
const accessors, audit history, and a small analysis class with low coupling.

## Exam-style deliverables

1. Implement only `src/*.cpp`.
2. Add at least four tests for each non-getter public operation.
3. Prove that an overdraft leaves both the balance and history unchanged.
4. Explain the precondition, postcondition, and invariant for
   `deductMoney`.

See [Wallet.mmd](docs/Wallet.mmd) and the supplied headers.
