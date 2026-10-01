#ifndef MIDSEM_WALLET_ANALYZER_H
#define MIDSEM_WALLET_ANALYZER_H

#include <ctime>

#include "Wallet.h"

class WalletAnalyzer {
private:
    const Wallet& wallet_;

public:
    explicit WalletAnalyzer(const Wallet& wallet);

    double totalAmountCredited() const;
    double totalAmountDebited() const;
    double expenditureBetween(std::time_t start, std::time_t end) const;
};

#endif
