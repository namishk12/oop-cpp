#include "Transaction.h"

#include <atomic>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace {

Transaction::Timestamp now()
{
    return std::chrono::system_clock::now();
}

std::string nextStandaloneTransactionId()
{
    static std::atomic<std::uint64_t> nextId{1};
    return "transaction-" + std::to_string(nextId.fetch_add(1));
}

}

Transaction::Transaction(std::string transactionId,
                         double amount,
                         bool creditTransaction,
                         Timestamp timestamp)
    : transactionId(std::move(transactionId)),
      amount(amount),
      creditTransaction(creditTransaction),
      timestamp(timestamp)
{
    validateAmount(amount);
}

Transaction::Transaction(std::string transactionId,
                         double amount,
                         bool creditTransaction)
    : Transaction(std::move(transactionId), amount, creditTransaction, now())
{
}

Transaction::Transaction(double amount, bool creditTransaction)
    : Transaction(nextStandaloneTransactionId(),
                  amount,
                  creditTransaction,
                  now())
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
    if (!std::isfinite(value) || value <= 0.0) {
        throw std::invalid_argument("Transaction amount must be finite and greater than zero");
    }
}
