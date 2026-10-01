#include <ctime>
#include <stdexcept>

#include <gtest/gtest.h>

#include "Transaction.h"
#include "Wallet.h"
#include "WalletAnalyzer.h"

TEST(Transaction, PreservesItsFields) {
    const Transaction transaction("t-1", 12.5, true, static_cast<std::time_t>(42));

    EXPECT_EQ(transaction.getTransactionId(), "t-1");
    EXPECT_DOUBLE_EQ(transaction.getAmount(), 12.5);
    EXPECT_TRUE(transaction.isCreditTransaction());
    EXPECT_EQ(transaction.getTimestamp(), static_cast<std::time_t>(42));
}

TEST(WalletConstruction, StartsWithTheOpeningBalance) {
    const Wallet wallet("alice@upi", 50.0);

    EXPECT_EQ(wallet.getWalletId(), "alice@upi");
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 50.0);
    EXPECT_TRUE(wallet.getTransactions().empty());
}

TEST(WalletConstruction, RejectsInvalidOpeningState) {
    EXPECT_THROW(Wallet("", 0.0), std::invalid_argument);
    EXPECT_THROW(Wallet("alice@upi", -1.0), std::invalid_argument);
}

TEST(Wallet, AddsMoneyAndRecordsAChronologicalCredit) {
    Wallet wallet("alice@upi");

    wallet.addMoney(25.0);

    ASSERT_EQ(wallet.getTransactions().size(), 1U);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 25.0);
    EXPECT_TRUE(wallet.getTransactions()[0].isCreditTransaction());
    EXPECT_DOUBLE_EQ(wallet.getTransactions()[0].getAmount(), 25.0);
    EXPECT_GE(wallet.getTransactions()[0].getTimestamp(), static_cast<std::time_t>(0));
}

TEST(Wallet, RejectsInvalidCreditsWithoutChangingState) {
    Wallet wallet("alice@upi", 10.0);

    EXPECT_THROW(wallet.addMoney(0.0), std::invalid_argument);
    EXPECT_THROW(wallet.addMoney(-5.0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 10.0);
    EXPECT_TRUE(wallet.getTransactions().empty());
}

TEST(Wallet, DeductsMoneyAndRecordsADebit) {
    Wallet wallet("alice@upi", 50.0);

    wallet.deductMoney(20.0);

    ASSERT_EQ(wallet.getTransactions().size(), 1U);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 30.0);
    EXPECT_FALSE(wallet.getTransactions()[0].isCreditTransaction());
    EXPECT_DOUBLE_EQ(wallet.getTransactions()[0].getAmount(), 20.0);
}

TEST(Wallet, RejectsInvalidOrOverdraftDebitsWithoutChangingState) {
    Wallet wallet("alice@upi", 50.0);
    wallet.addMoney(10.0);
    const std::size_t transactionCount = wallet.getTransactions().size();

    EXPECT_THROW(wallet.deductMoney(0.0), std::invalid_argument);
    EXPECT_THROW(wallet.deductMoney(-1.0), std::invalid_argument);
    EXPECT_THROW(wallet.deductMoney(100.0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 60.0);
    EXPECT_EQ(wallet.getTransactions().size(), transactionCount);
}

TEST(WalletAnalyzer, SeparatesCreditsAndDebits) {
    Wallet wallet("alice@upi", 10.0);
    wallet.addMoney(25.0);
    wallet.deductMoney(5.0);
    wallet.addMoney(15.0);
    wallet.deductMoney(8.0);
    const WalletAnalyzer analyzer(wallet);

    EXPECT_DOUBLE_EQ(analyzer.totalAmountCredited(), 40.0);
    EXPECT_DOUBLE_EQ(analyzer.totalAmountDebited(), 13.0);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 37.0);
}

TEST(WalletAnalyzer, IncludesTransactionsInAnInclusiveTimeRange) {
    Wallet wallet("alice@upi");
    wallet.addMoney(20.0);
    wallet.deductMoney(7.0);
    const WalletAnalyzer analyzer(wallet);
    const std::time_t now = std::time(nullptr);

    EXPECT_DOUBLE_EQ(analyzer.expenditureBetween(now - 5, now + 5), 7.0);
    EXPECT_DOUBLE_EQ(analyzer.expenditureBetween(now + 10, now + 20), 0.0);
}

TEST(WalletAnalyzer, RejectsReversedTimeRanges) {
    const Wallet wallet("alice@upi");
    const WalletAnalyzer analyzer(wallet);

    EXPECT_THROW(analyzer.expenditureBetween(10, 9), std::invalid_argument);
}
