#ifndef MIDSEM_WALLET_H
#define MIDSEM_WALLET_H

#include <string>
#include <vector>

#include "Transaction.h"

class Wallet {
private:
    std::string walletId_;
    double balance_;
    std::vector<Transaction> transactions_;
    int nextTransactionNumber_;

public:
    explicit Wallet(std::string walletId, double openingBalance = 0.0);

    void addMoney(double amount);
    void deductMoney(double amount);

    double getBalance() const;
    std::string getWalletId() const;
    const std::vector<Transaction>& getTransactions() const;
};

#endif
