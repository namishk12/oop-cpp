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

double WalletAnalyzer::expenditureBetween(Transaction::Timestamp startTimestamp,
                                          Transaction::Timestamp endTimestamp) const
{
    if (startTimestamp > endTimestamp) {
        throw std::invalid_argument("startTimestamp cannot be after endTimestamp");
    }

    double expenditure = 0.0;
    for (const Transaction& transaction : wallet.getTransactions()) {
        const Transaction::Timestamp timestamp = transaction.getTimestamp();
        const bool inRange = timestamp >= startTimestamp && timestamp <= endTimestamp;
        if (inRange && !transaction.isCreditTransaction()) {
            expenditure += transaction.getAmount();
        }
    }
    return expenditure;
}
