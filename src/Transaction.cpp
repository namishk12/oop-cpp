#include "Transaction.h"

#include <stdexcept>

namespace {

std::string nextStandaloneTransactionId()
{
    static unsigned long long nextId = 1;
    return "transaction-" + std::to_string(nextId++);
}

}

Transaction::Transaction(std::string transactionId,
                         double amount,
                         bool creditTransaction,
                         Timestamp timestamp)
    : transactionId(transactionId),
      amount(amount),
      creditTransaction(creditTransaction),
      timestamp(timestamp)
{
    validateAmount(amount);
}

Transaction::Transaction(std::string transactionId,
                         double amount,
                         bool creditTransaction)
    : Transaction(transactionId, amount, creditTransaction, std::time(nullptr))
{
}

Transaction::Transaction(double amount, bool creditTransaction)
    : Transaction(nextStandaloneTransactionId(),
                  amount,
                  creditTransaction,
                  std::time(nullptr))
{
}

const std::string& Transaction::getTransactionId() const noexcept
{
    return transactionId;
}

const std::string& Transaction::getTransactionID() const noexcept
{
    return getTransactionId();
}

double Transaction::getAmount() const noexcept
{
    return amount;
}

bool Transaction::isCreditTransaction() const noexcept
{
    return creditTransaction;
}

bool Transaction::getCreditTransaction() const noexcept
{
    return isCreditTransaction();
}

Transaction::Timestamp Transaction::getTimestamp() const noexcept
{
    return timestamp;
}

void Transaction::validateAmount(double value)
{
    if (value != value || value <= 0.0) {
        throw std::invalid_argument("Transaction amount must be greater than zero");
    }
}
