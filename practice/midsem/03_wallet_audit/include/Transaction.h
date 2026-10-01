#ifndef MIDSEM_TRANSACTION_H
#define MIDSEM_TRANSACTION_H

#include <ctime>
#include <string>

class Transaction {
private:
    std::string transactionId_;
    double amount_;
    bool creditTransaction_;
    std::time_t timestamp_;

public:
    Transaction(std::string transactionId,
                double amount,
                bool creditTransaction,
                std::time_t timestamp);

    std::string getTransactionId() const;
    double getAmount() const;
    bool isCreditTransaction() const;
    std::time_t getTimestamp() const;
};

#endif
