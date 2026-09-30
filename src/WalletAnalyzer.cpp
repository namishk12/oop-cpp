#include "WalletAnalyzer.h"

#include <stdexcept>

WalletAnalyzer::WalletAnalyzer(const Wallet& wallet)
    : wallet(wallet)
{
}

double WalletAnalyzer::totalAmountCredited() const
{
    double total = 0.0;
    for (const Transaction& transaction : wallet.getTransactions()) {
        if (transaction.isCreditTransaction()) {
            total += transaction.getAmount();
        }
    }
    return total;
}

double WalletAnalyzer::totalAmountDebited() const
{
    double total = 0.0;
    for (const Transaction& transaction : wallet.getTransactions()) {
        if (!transaction.isCreditTransaction()) {
            total += transaction.getAmount();
        }
    }
    return total;
}

double WalletAnalyzer::expenditureBetween(Transaction::Timestamp startDate,
                                          Transaction::Timestamp endDate) const
{
    if (startDate > endDate) {
        throw std::invalid_argument("startDate cannot be after endDate");
    }

    double expenditure = 0.0;
    for (const Transaction& transaction : wallet.getTransactions()) {
        const Transaction::Timestamp timestamp = transaction.getTimestamp();
        const bool inRange = timestamp >= startDate && timestamp <= endDate;
        if (inRange && !transaction.isCreditTransaction()) {
            expenditure += transaction.getAmount();
        }
    }
    return expenditure;
}
