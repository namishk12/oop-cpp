#include "WalletAnalyzer.h"

#include <stdexcept>

WalletAnalyzer::WalletAnalyzer(const Wallet& wallet)
    : wallet_(wallet) {
}

double WalletAnalyzer::totalAmountCredited() const {
    // TODO: sum credit transactions only.
    return 0.0;
}

double WalletAnalyzer::totalAmountDebited() const {
    // TODO: sum debit transactions only.
    return 0.0;
}

double WalletAnalyzer::expenditureBetween(std::time_t start,
                                          std::time_t end) const {
    (void)start;
    (void)end;
    // TODO: validate the range and sum inclusive debit timestamps.
    return 0.0;
}
