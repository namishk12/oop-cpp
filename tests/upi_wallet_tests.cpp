#include "WalletAnalyzer.h"

#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

using Timestamp = Transaction::Timestamp;

const Timestamp baseTime = Timestamp(std::chrono::hours(24 * 20000));

Wallet makeWallet(double initialBalance = 100.0)
{
    return Wallet("alice@upi", initialBalance, [] { return baseTime; });
}

void expect(bool condition, const std::string& message)
{
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void expectNear(double actual, double expected, const std::string& message)
{
    if (std::abs(actual - expected) > 1e-9) {
        throw std::runtime_error(message);
    }
}

template <typename Exception, typename Function>
void expectThrows(Function&& function, const std::string& message)
{
    bool threwExpected = false;
    try {
        function();
    } catch (const Exception&) {
        threwExpected = true;
    } catch (...) {
        throw std::runtime_error(message + " (wrong exception type)");
    }
    expect(threwExpected, message);
}

void transactionStoresItsDetails()
{
    const Timestamp timestamp = baseTime;
    Transaction transaction("txn-1", 125.50, true, timestamp);

    expect(transaction.getTransactionId() == "txn-1", "transaction id was not stored");
    expectNear(transaction.getAmount(), 125.50, "transaction amount was not stored");
    expect(transaction.isCreditTransaction(), "credit flag was not stored");
    expect(transaction.getTimestamp() == timestamp, "timestamp was not stored");
}

void transactionRejectsInvalidAmounts()
{
    expectThrows<std::invalid_argument>(
        [] { Transaction("txn-negative", -1.0, true, baseTime); },
        "negative transaction amount should be rejected");
    expectThrows<std::invalid_argument>(
        [] { Transaction("txn-zero", 0.0, true, baseTime); },
        "zero transaction amount should be rejected");
    expectThrows<std::invalid_argument>(
        [] { Transaction("txn-nan", std::nan(""), true, baseTime); },
        "NaN transaction amount should be rejected");
}

void addMoneyIncreasesBalanceAndRecordsCredit()
{
    Wallet wallet = makeWallet();
    wallet.addMoney(25.50);

    expectNear(wallet.getBalance(), 125.50, "addMoney did not increase balance");
    const std::vector<Transaction> transactions = wallet.getTransactions();
    expect(transactions.size() == 1, "addMoney did not add an audit entry");
    expectNear(transactions[0].getAmount(), 25.50, "credit amount was not recorded");
    expect(transactions[0].isCreditTransaction(), "credit transaction flag was incorrect");
}

void addMoneyPreservesOrderAndUniqueIds()
{
    Wallet wallet = makeWallet(0.0);
    wallet.addMoney(10.0);
    wallet.addMoney(20.0);

    const std::vector<Transaction> transactions = wallet.getTransactions();
    expect(transactions.size() == 2, "credit audit length is incorrect");
    expectNear(transactions[0].getAmount(), 10.0, "first transaction is out of order");
    expectNear(transactions[1].getAmount(), 20.0, "second transaction is out of order");
    expect(transactions[0].getTransactionId() != transactions[1].getTransactionId(),
           "transaction ids should be unique");
    expect(transactions[0].getTimestamp() <= transactions[1].getTimestamp(),
           "transactions should be chronological");
}

void addMoneyRejectsInvalidAmountsWithoutMutation()
{
    Wallet wallet = makeWallet();
    expectThrows<std::invalid_argument>([&] { wallet.addMoney(-5.0); },
                                        "negative add should be rejected");
    expectThrows<std::invalid_argument>([&] { wallet.addMoney(0.0); },
                                        "zero add should be rejected");
    expectThrows<std::invalid_argument>([&] { wallet.addMoney(std::nan("")); },
                                        "NaN add should be rejected");

    expectNear(wallet.getBalance(), 100.0, "invalid add changed balance");
    expect(wallet.getTransactions().empty(), "invalid add changed audit");
}

void addMoneyRejectsOverflowWithoutMutation()
{
    Wallet wallet = makeWallet(std::numeric_limits<double>::max());

    expectThrows<std::invalid_argument>([&] { wallet.addMoney(1.0); },
                                        "overflowing add should be rejected");
    expect(wallet.getBalance() == std::numeric_limits<double>::max(),
           "overflowing add changed balance");
    expect(wallet.getTransactions().empty(), "overflowing add changed audit");
}

void deductMoneyDecreasesBalanceAndRecordsDebit()
{
    Wallet wallet = makeWallet();
    wallet.deductMoney(25.50);

    expectNear(wallet.getBalance(), 74.50, "deductMoney did not decrease balance");
    const std::vector<Transaction> transactions = wallet.getTransactions();
    expect(transactions.size() == 1, "deductMoney did not add an audit entry");
    expectNear(transactions[0].getAmount(), 25.50, "debit amount was not recorded");
    expect(!transactions[0].isCreditTransaction(), "debit transaction flag was incorrect");
}

void deductMoneyAllowsExactBalance()
{
    Wallet wallet = makeWallet();
    wallet.deductMoney(100.0);

    expectNear(wallet.getBalance(), 0.0, "exact deduction did not empty wallet");
    expect(wallet.getTransactions().size() == 1, "exact deduction was not recorded");
}

void deductMoneyRejectsInsufficientFundsWithoutMutation()
{
    Wallet wallet = makeWallet();
    expectThrows<std::invalid_argument>([&] { wallet.deductMoney(100.01); },
                                        "overdraft should be rejected");

    expectNear(wallet.getBalance(), 100.0, "overdraft changed balance");
    expect(wallet.getTransactions().empty(), "overdraft changed audit");
}

void deductMoneyRejectsInvalidAmountsWithoutMutation()
{
    Wallet wallet = makeWallet();
    expectThrows<std::invalid_argument>([&] { wallet.deductMoney(-1.0); },
                                        "negative deduction should be rejected");
    expectThrows<std::invalid_argument>([&] { wallet.deductMoney(0.0); },
                                        "zero deduction should be rejected");
    expectThrows<std::invalid_argument>([&] { wallet.deductMoney(std::nan("")); },
                                        "NaN deduction should be rejected");

    expectNear(wallet.getBalance(), 100.0, "invalid deduction changed balance");
    expect(wallet.getTransactions().empty(), "invalid deduction changed audit");
}

void totalAmountCreditedSumsOnlyCredits()
{
    Wallet wallet = makeWallet();
    wallet.addMoney(25.0);
    wallet.deductMoney(10.0);
    wallet.addMoney(50.0);

    expectNear(WalletAnalyzer(wallet).totalAmountCredited(), 75.0,
               "credit total is incorrect");
}

void totalAmountCreditedIsZeroWithoutCredits()
{
    Wallet wallet = makeWallet();
    wallet.deductMoney(20.0);

    expectNear(WalletAnalyzer(wallet).totalAmountCredited(), 0.0,
               "credit total should be zero");
}

void totalAmountCreditedUpdatesAfterLaterCredits()
{
    Wallet wallet = makeWallet();
    WalletAnalyzer analyzer(wallet);
    wallet.addMoney(10.0);
    expectNear(analyzer.totalAmountCredited(), 10.0, "credit total did not update");
    wallet.addMoney(15.0);
    expectNear(analyzer.totalAmountCredited(), 25.0, "credit total update is incorrect");
}

void totalAmountCreditedDoesNotCountOpeningBalance()
{
    Wallet wallet = makeWallet(100.0);

    expectNear(WalletAnalyzer(wallet).totalAmountCredited(), 0.0,
               "opening balance should not be counted as a credit");
}

void totalAmountDebitedSumsOnlyDebits()
{
    Wallet wallet = makeWallet();
    wallet.addMoney(25.0);
    wallet.deductMoney(10.0);
    wallet.deductMoney(15.0);

    expectNear(WalletAnalyzer(wallet).totalAmountDebited(), 25.0,
               "debit total is incorrect");
}

void totalAmountDebitedIsZeroWithoutDebits()
{
    Wallet wallet = makeWallet();
    wallet.addMoney(20.0);

    expectNear(WalletAnalyzer(wallet).totalAmountDebited(), 0.0,
               "debit total should be zero");
}

void totalAmountDebitedUpdatesAfterLaterDebits()
{
    Wallet wallet = makeWallet();
    WalletAnalyzer analyzer(wallet);
    wallet.deductMoney(10.0);
    expectNear(analyzer.totalAmountDebited(), 10.0, "debit total did not update");
    wallet.deductMoney(15.0);
    expectNear(analyzer.totalAmountDebited(), 25.0, "debit total update is incorrect");
}

void totalAmountDebitedDoesNotCountOpeningBalance()
{
    Wallet wallet = makeWallet(100.0);

    expectNear(WalletAnalyzer(wallet).totalAmountDebited(), 0.0,
               "opening balance should not be counted as a debit");
}

void expenditureBetweenIncludesBoundariesAndExcludesCredits()
{
    Wallet wallet = makeWallet();
    wallet.deductMoney(10.0);
    wallet.addMoney(50.0);
    wallet.deductMoney(15.0);

    expectNear(WalletAnalyzer(wallet).expenditureBetween(baseTime, baseTime), 25.0,
               "date-range expenditure is incorrect");
}

void expenditureBetweenReturnsZeroOutsideRange()
{
    Wallet wallet = makeWallet();
    wallet.deductMoney(10.0);
    const Timestamp before = baseTime - std::chrono::hours(24);

    expectNear(WalletAnalyzer(wallet).expenditureBetween(before, before), 0.0,
               "outside date range should have no expenditure");
}

void expenditureBetweenReturnsZeroWithoutDebits()
{
    Wallet wallet = makeWallet();
    wallet.addMoney(20.0);

    expectNear(WalletAnalyzer(wallet).expenditureBetween(baseTime, baseTime), 0.0,
               "credits should not count as expenditure");
}

void expenditureBetweenRejectsReversedRange()
{
    Wallet wallet = makeWallet();
    expectThrows<std::invalid_argument>(
        [&] { WalletAnalyzer(wallet).expenditureBetween(baseTime, baseTime - std::chrono::seconds(1)); },
        "reversed date range should be rejected");
}

void transactionSnapshotProtectsWalletAudit()
{
    Wallet wallet = makeWallet(0.0);
    wallet.addMoney(10.0);
    std::vector<Transaction> snapshot = wallet.getTransactions();
    snapshot.clear();

    expect(wallet.getTransactions().size() == 1, "transaction snapshot changed wallet audit");
}

struct TestCase {
    const char* name;
    std::function<void()> function;
};

}

int main()
{
    const std::vector<TestCase> tests{
        {"transactionStoresItsDetails", transactionStoresItsDetails},
        {"transactionRejectsInvalidAmounts", transactionRejectsInvalidAmounts},
        {"addMoneyIncreasesBalanceAndRecordsCredit", addMoneyIncreasesBalanceAndRecordsCredit},
        {"addMoneyPreservesOrderAndUniqueIds", addMoneyPreservesOrderAndUniqueIds},
        {"addMoneyRejectsInvalidAmountsWithoutMutation", addMoneyRejectsInvalidAmountsWithoutMutation},
        {"addMoneyRejectsOverflowWithoutMutation", addMoneyRejectsOverflowWithoutMutation},
        {"deductMoneyDecreasesBalanceAndRecordsDebit", deductMoneyDecreasesBalanceAndRecordsDebit},
        {"deductMoneyAllowsExactBalance", deductMoneyAllowsExactBalance},
        {"deductMoneyRejectsInsufficientFundsWithoutMutation", deductMoneyRejectsInsufficientFundsWithoutMutation},
        {"deductMoneyRejectsInvalidAmountsWithoutMutation", deductMoneyRejectsInvalidAmountsWithoutMutation},
        {"totalAmountCreditedSumsOnlyCredits", totalAmountCreditedSumsOnlyCredits},
        {"totalAmountCreditedIsZeroWithoutCredits", totalAmountCreditedIsZeroWithoutCredits},
        {"totalAmountCreditedUpdatesAfterLaterCredits", totalAmountCreditedUpdatesAfterLaterCredits},
        {"totalAmountCreditedDoesNotCountOpeningBalance", totalAmountCreditedDoesNotCountOpeningBalance},
        {"totalAmountDebitedSumsOnlyDebits", totalAmountDebitedSumsOnlyDebits},
        {"totalAmountDebitedIsZeroWithoutDebits", totalAmountDebitedIsZeroWithoutDebits},
        {"totalAmountDebitedUpdatesAfterLaterDebits", totalAmountDebitedUpdatesAfterLaterDebits},
        {"totalAmountDebitedDoesNotCountOpeningBalance", totalAmountDebitedDoesNotCountOpeningBalance},
        {"expenditureBetweenIncludesBoundariesAndExcludesCredits", expenditureBetweenIncludesBoundariesAndExcludesCredits},
        {"expenditureBetweenReturnsZeroOutsideRange", expenditureBetweenReturnsZeroOutsideRange},
        {"expenditureBetweenReturnsZeroWithoutDebits", expenditureBetweenReturnsZeroWithoutDebits},
        {"expenditureBetweenRejectsReversedRange", expenditureBetweenRejectsReversedRange},
        {"transactionSnapshotProtectsWalletAudit", transactionSnapshotProtectsWalletAudit},
    };

    std::size_t passed = 0;
    for (const TestCase& test : tests) {
        try {
            test.function();
            ++passed;
            std::cout << "[PASS] " << test.name << '\n';
        } catch (const std::exception& error) {
            std::cerr << "[FAIL] " << test.name << ": " << error.what() << '\n';
            return 1;
        }
    }

    std::cout << passed << " tests passed\n";
    return 0;
}
