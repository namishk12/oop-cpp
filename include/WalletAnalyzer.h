#pragma once

#include "Wallet.h"

class WalletAnalyzer {
public:
    explicit WalletAnalyzer(const Wallet& wallet);

    double totalAmountCredited() const;
    double totalAmountDebited() const;
    double expenditureBetween(Transaction::Timestamp startTimestamp,
                              Transaction::Timestamp endTimestamp) const;

private:
    const Wallet& wallet;
};
