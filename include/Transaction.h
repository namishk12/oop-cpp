#pragma once

#include <ctime>
#include <string>

class Transaction {
public:
    using Timestamp = std::time_t;

    Transaction(std::string transactionId,
                double amount,
                bool creditTransaction,
                Timestamp timestamp);

    Transaction(std::string transactionId,
                double amount,
                bool creditTransaction);

    Transaction(double amount, bool creditTransaction);

    const std::string& getTransactionId() const noexcept;
    const std::string& getTransactionID() const noexcept;
    double getAmount() const noexcept;
    bool isCreditTransaction() const noexcept;
    bool getCreditTransaction() const noexcept;
    Timestamp getTimestamp() const noexcept;

private:
    static void validateAmount(double amount);

    std::string transactionId;
    double amount;
    bool creditTransaction;
    Timestamp timestamp;
};
