#pragma once

#include "Transaction.h"

#include <string>
#include <vector>

class Wallet {
public:
    Wallet();
    explicit Wallet(std::string upiId);
    Wallet(std::string upiId, double initialBalance);

    void addMoney(double amount);
    void deductMoney(double amount);

    const std::string& getUpiId() const noexcept;
    const std::string& getUPIId() const noexcept;
    double getBalance() const noexcept;
    std::vector<Transaction> getTransactions() const;
    std::size_t getTransactionCount() const noexcept;

private:
    static void validateInitialBalance(double initialBalance);
    static void validateTransactionAmount(double amount);

    Transaction createTransaction(double amount, bool credit) const;
    void appendTransaction(Transaction transaction);

    std::string upiId;
    double balance;
    std::vector<Transaction> transactions;
};
