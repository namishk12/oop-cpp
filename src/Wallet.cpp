#include "Wallet.h"

#include <ctime>
#include <stdexcept>

namespace {

std::string nextTransactionId()
{
    static unsigned long long nextId = 1;
    return "transaction-" + std::to_string(nextId++);
}

}

Wallet::Wallet()
    : Wallet("", 0.0)
{
}

Wallet::Wallet(std::string upiId)
    : Wallet(upiId, 0.0)
{
}

Wallet::Wallet(std::string upiId, double initialBalance)
    : upiId(upiId),
      balance(initialBalance)
{
    validateInitialBalance(initialBalance);
}

void Wallet::addMoney(double amount)
{
    validateTransactionAmount(amount);
    const double newBalance = balance + amount;

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
    if (initialBalance != initialBalance || initialBalance < 0.0) {
        throw std::invalid_argument("Initial balance must be non-negative");
    }
}

void Wallet::validateTransactionAmount(double amount)
{
    if (amount != amount || amount <= 0.0) {
        throw std::invalid_argument("Amount must be greater than zero");
    }
}

Transaction Wallet::createTransaction(double amount, bool credit) const
{
    return Transaction(nextTransactionId(), amount, credit, std::time(nullptr));
}

void Wallet::appendTransaction(Transaction transaction)
{
    transactions.push_back(transaction);
}
