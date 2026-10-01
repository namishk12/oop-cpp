#include "Wallet.h"

#include <stdexcept>
#include <utility>

Wallet::Wallet(std::string walletId, double openingBalance)
    : walletId_(std::move(walletId)),
      balance_(openingBalance),
      nextTransactionNumber_(1) {
    // TODO: reject an empty id and a negative opening balance.
}

void Wallet::addMoney(double amount) {
    (void)amount;
    // TODO: validate, update balance, and append a credit transaction.
}

void Wallet::deductMoney(double amount) {
    (void)amount;
    // TODO: validate, preserve state on failure, and append a debit.
}

double Wallet::getBalance() const {
    return balance_;
}

std::string Wallet::getWalletId() const {
    return walletId_;
}

const std::vector<Transaction>& Wallet::getTransactions() const {
    return transactions_;
}
