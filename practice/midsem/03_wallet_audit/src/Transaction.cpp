#include "Transaction.h"

#include <utility>

Transaction::Transaction(std::string transactionId,
                         double amount,
                         bool creditTransaction,
                         std::time_t timestamp)
    : transactionId_(std::move(transactionId)),
      amount_(amount),
      creditTransaction_(creditTransaction),
      timestamp_(timestamp) {
}

std::string Transaction::getTransactionId() const {
    return transactionId_;
}

double Transaction::getAmount() const {
    return amount_;
}

bool Transaction::isCreditTransaction() const {
    return creditTransaction_;
}

std::time_t Transaction::getTimestamp() const {
    return timestamp_;
}
