#include "Transaction.h"
#include "Wallet.h"
#include "WalletAnalyzer.h"

#include <gtest/gtest.h>

#include <ctime>
#include <stdexcept>
#include <vector>

TEST(TransactionTest, StoresAllFields)
{
    const std::time_t timestamp = std::time(nullptr);
    const Transaction transaction("txn-1", 125.50, true, timestamp);

    EXPECT_EQ(transaction.getTransactionId(), "txn-1");
    EXPECT_DOUBLE_EQ(transaction.getAmount(), 125.50);
    EXPECT_TRUE(transaction.isCreditTransaction());
    EXPECT_EQ(transaction.getTimestamp(), timestamp);
}

TEST(TransactionTest, RejectsNonPositiveAmounts)
{
    EXPECT_THROW(Transaction("negative", -1.0, true, 1), std::invalid_argument);
    EXPECT_THROW(Transaction("zero", 0.0, true, 1), std::invalid_argument);
}

TEST(WalletTest, StartsWithTheGivenBalanceAndEmptyAudit)
{
    const Wallet wallet("alice@upi", 100.0);

    EXPECT_EQ(wallet.getUpiId(), "alice@upi");
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 100.0);
    EXPECT_TRUE(wallet.getTransactions().empty());
}

TEST(WalletTest, AddMoneyIncreasesBalanceAndRecordsCredit)
{
    Wallet wallet("alice@upi", 100.0);

    wallet.addMoney(25.50);

    ASSERT_EQ(wallet.getTransactions().size(), 1U);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 125.50);
    EXPECT_DOUBLE_EQ(wallet.getTransactions()[0].getAmount(), 25.50);
    EXPECT_TRUE(wallet.getTransactions()[0].isCreditTransaction());
}

TEST(WalletTest, AddMoneyPreservesTransactionOrder)
{
    Wallet wallet("alice@upi", 0.0);
    wallet.addMoney(10.0);
    wallet.addMoney(20.0);

    const std::vector<Transaction> transactions = wallet.getTransactions();
    ASSERT_EQ(transactions.size(), 2U);
    EXPECT_DOUBLE_EQ(transactions[0].getAmount(), 10.0);
    EXPECT_DOUBLE_EQ(transactions[1].getAmount(), 20.0);
    EXPECT_NE(transactions[0].getTransactionId(), transactions[1].getTransactionId());
}

TEST(WalletTest, AddMoneyRejectsNegativeWithoutMutation)
{
    Wallet wallet("alice@upi", 100.0);

    EXPECT_THROW(wallet.addMoney(-5.0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 100.0);
    EXPECT_TRUE(wallet.getTransactions().empty());
}

TEST(WalletTest, AddMoneyRejectsZeroWithoutMutation)
{
    Wallet wallet("alice@upi", 100.0);

    EXPECT_THROW(wallet.addMoney(0.0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 100.0);
    EXPECT_TRUE(wallet.getTransactions().empty());
}

TEST(WalletTest, DeductMoneyDecreasesBalanceAndRecordsDebit)
{
    Wallet wallet("alice@upi", 100.0);

    wallet.deductMoney(25.50);

    ASSERT_EQ(wallet.getTransactions().size(), 1U);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 74.50);
    EXPECT_DOUBLE_EQ(wallet.getTransactions()[0].getAmount(), 25.50);
    EXPECT_FALSE(wallet.getTransactions()[0].isCreditTransaction());
}

TEST(WalletTest, DeductMoneyAllowsExactBalance)
{
    Wallet wallet("alice@upi", 100.0);

    wallet.deductMoney(100.0);

    EXPECT_DOUBLE_EQ(wallet.getBalance(), 0.0);
    EXPECT_EQ(wallet.getTransactionCount(), 1U);
}

TEST(WalletTest, DeductMoneyRejectsOverdraftWithoutMutation)
{
    Wallet wallet("alice@upi", 100.0);

    EXPECT_THROW(wallet.deductMoney(100.01), std::invalid_argument);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 100.0);
    EXPECT_TRUE(wallet.getTransactions().empty());
}

TEST(WalletTest, DeductMoneyRejectsNegativeWithoutMutation)
{
    Wallet wallet("alice@upi", 100.0);

    EXPECT_THROW(wallet.deductMoney(-1.0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(wallet.getBalance(), 100.0);
    EXPECT_TRUE(wallet.getTransactions().empty());
}

TEST(WalletTest, TransactionGetterReturnsASnapshot)
{
    Wallet wallet("alice@upi", 0.0);
    wallet.addMoney(10.0);
    std::vector<Transaction> snapshot = wallet.getTransactions();
    snapshot.clear();

    EXPECT_EQ(wallet.getTransactionCount(), 1U);
}

TEST(WalletAnalyzerTest, TotalsSeparateCreditsAndDebits)
{
    Wallet wallet("alice@upi", 100.0);
    wallet.addMoney(25.0);
    wallet.deductMoney(10.0);
    wallet.addMoney(50.0);
    wallet.deductMoney(15.0);
    const WalletAnalyzer analyzer(wallet);

    EXPECT_DOUBLE_EQ(analyzer.totalAmountCredited(), 75.0);
    EXPECT_DOUBLE_EQ(analyzer.totalAmountDebited(), 25.0);
}

TEST(WalletAnalyzerTest, TotalsAreZeroWhenThereAreNoMatchingTransactions)
{
    Wallet wallet("alice@upi", 100.0);
    const WalletAnalyzer analyzer(wallet);

    EXPECT_DOUBLE_EQ(analyzer.totalAmountCredited(), 0.0);
    EXPECT_DOUBLE_EQ(analyzer.totalAmountDebited(), 0.0);
}

TEST(WalletAnalyzerTest, TotalsChangeWhenWalletChanges)
{
    Wallet wallet("alice@upi", 100.0);
    const WalletAnalyzer analyzer(wallet);

    wallet.addMoney(10.0);
    EXPECT_DOUBLE_EQ(analyzer.totalAmountCredited(), 10.0);
    wallet.deductMoney(5.0);
    EXPECT_DOUBLE_EQ(analyzer.totalAmountDebited(), 5.0);
}

TEST(WalletAnalyzerTest, OpeningBalanceIsNotATransaction)
{
    const Wallet wallet("alice@upi", 100.0);
    const WalletAnalyzer analyzer(wallet);

    EXPECT_DOUBLE_EQ(analyzer.totalAmountCredited(), 0.0);
    EXPECT_DOUBLE_EQ(analyzer.totalAmountDebited(), 0.0);
}

TEST(WalletAnalyzerTest, ExpenditureUsesInclusiveTimestampBoundaries)
{
    Wallet wallet("alice@upi", 100.0);
    wallet.deductMoney(10.0);
    wallet.addMoney(50.0);
    wallet.deductMoney(15.0);
    const std::vector<Transaction> transactions = wallet.getTransactions();
    const WalletAnalyzer analyzer(wallet);

    EXPECT_DOUBLE_EQ(analyzer.expenditureBetween(
                         transactions.front().getTimestamp(),
                         transactions.back().getTimestamp()),
                     25.0);
}

TEST(WalletAnalyzerTest, ExpenditureExcludesCredits)
{
    Wallet wallet("alice@upi", 100.0);
    wallet.addMoney(50.0);
    const std::time_t timestamp = wallet.getTransactions().front().getTimestamp();
    const WalletAnalyzer analyzer(wallet);

    EXPECT_DOUBLE_EQ(analyzer.expenditureBetween(timestamp, timestamp), 0.0);
}

TEST(WalletAnalyzerTest, ExpenditureReturnsZeroOutsideRange)
{
    Wallet wallet("alice@upi", 100.0);
    wallet.deductMoney(10.0);
    const std::time_t timestamp = wallet.getTransactions().front().getTimestamp();
    const WalletAnalyzer analyzer(wallet);

    EXPECT_DOUBLE_EQ(analyzer.expenditureBetween(timestamp - 1, timestamp - 1), 0.0);
}

TEST(WalletAnalyzerTest, ExpenditureRejectsReversedRange)
{
    const Wallet wallet("alice@upi", 100.0);
    const WalletAnalyzer analyzer(wallet);

    EXPECT_THROW(analyzer.expenditureBetween(2, 1), std::invalid_argument);
}
