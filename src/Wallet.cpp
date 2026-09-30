#include "Wallet.h"

#include <atomic>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace {

Transaction::Timestamp systemNow()
{
    return std::chrono::system_clock::now();
}

std::string nextTransactionId()
{
    static std::atomic<std::uint64_t> nextId{1};
    return "transaction-" + std::to_string(nextId.fetch_add(1));
}

}

Wallet::Wallet()
    : Wallet("", 0.0)
{
}

Wallet::Wallet(std::string upiId)
    : Wallet(std::move(upiId), 0.0)
{
}

Wallet::Wallet(std::string upiId, double initialBalance)
    : Wallet(std::move(upiId), initialBalance, systemNow)
{
}

Wallet::Wallet(std::string upiId, double initialBalance, Clock clock)
    : upiId(std::move(upiId)),
      balance(initialBalance),
      clock(std::move(clock))
{
    validateInitialBalance(initialBalance);
    if (!this->clock) {
        throw std::invalid_argument("clock cannot be empty");
    }
}

void Wallet::addMoney(double amount)
{
    validateTransactionAmount(amount);
    const double newBalance = balance + amount;
    if (!std::isfinite(newBalance)) {
        throw std::invalid_argument("Balance cannot exceed the finite double range");
    }

    appendTransaction(createTransaction(amount, true));
    balance = newBalance;
}

void Wallet::deductMoney(double amount)
{
    validateTransactionAmount(amount);
    if (amount > balance) {
        throw std::invalid_argument("Insufficient wallet balance");
    }

    appendTransaction(createTransaction(amount, false));
    balance -= amount;
    if (balance == -0.0) {
        balance = 0.0;
    }
}

const std::string& Wallet::getUpiId() const noexcept
{
    return upiId;
}

const std::string& Wallet::getUPIId() const noexcept
{
    return getUpiId();
}

double Wallet::getBalance() const noexcept
{
    return balance;
}

std::vector<Transaction> Wallet::getTransactions() const
{
    return transactions;
}

std::size_t Wallet::getTransactionCount() const noexcept
{
    return transactions.size();
}

void Wallet::validateInitialBalance(double initialBalance)
{
    if (!std::isfinite(initialBalance) || initialBalance < 0.0) {
        throw std::invalid_argument("Initial balance must be finite and non-negative");
    }
}

void Wallet::validateTransactionAmount(double amount)
{
    if (!std::isfinite(amount) || amount <= 0.0) {
        throw std::invalid_argument("Amount must be finite and greater than zero");
    }
}

Transaction Wallet::createTransaction(double amount, bool credit) const
{
    return Transaction(nextTransactionId(), amount, credit, clock());
}

void Wallet::appendTransaction(Transaction transaction)
{
    transactions.push_back(std::move(transaction));
}
