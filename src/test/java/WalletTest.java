import org.junit.jupiter.api.Test;

import java.time.Clock;
import java.time.Instant;
import java.time.ZoneOffset;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

class WalletTest {

    private static final Clock TEST_CLOCK = Clock.fixed(
            Instant.parse("2026-01-01T12:00:00Z"), ZoneOffset.UTC);

    @Test
    void startsWithAnEmptyTransactionAudit() {
        Wallet wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);

        assertEquals("alice@upi", wallet.getUpiId());
        assertEquals(100.0, wallet.getBalance());
        assertEquals(0, wallet.getTransactions().length);
    }

    @Test
    void addMoneyIncreasesBalanceAndRecordsCredit() {
        Wallet wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);

        wallet.addMoney(25.50);

        assertEquals(125.50, wallet.getBalance());
        Transaction[] transactions = wallet.getTransactions();
        assertEquals(1, transactions.length);
        assertEquals(25.50, transactions[0].getAmount());
        assertTrue(transactions[0].isCreditTransaction());
    }

    @Test
    void addMoneyPreservesChronologicalOrderAndUniqueIds() {
        Wallet wallet = new Wallet("alice@upi", 0.0, TEST_CLOCK);

        wallet.addMoney(10.0);
        wallet.addMoney(20.0);

        Transaction[] transactions = wallet.getTransactions();
        assertEquals(2, transactions.length);
        assertEquals(10.0, transactions[0].getAmount());
        assertEquals(20.0, transactions[1].getAmount());
        assertNotEquals(transactions[0].getTransactionId(), transactions[1].getTransactionId());
        assertFalse(transactions[0].getTimestamp().isAfter(transactions[1].getTimestamp()));
    }

    @Test
    void addMoneyRejectsNegativeAmountWithoutChangingState() {
        Wallet wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);

        assertThrows(IllegalArgumentException.class, () -> wallet.addMoney(-5.0));

        assertEquals(100.0, wallet.getBalance());
        assertEquals(0, wallet.getTransactions().length);
    }

    @Test
    void addMoneyRejectsZeroAndNonFiniteAmountsWithoutChangingState() {
        Wallet wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);

        assertThrows(IllegalArgumentException.class, () -> wallet.addMoney(0.0));
        assertThrows(IllegalArgumentException.class, () -> wallet.addMoney(Double.NaN));
        assertThrows(IllegalArgumentException.class, () -> wallet.addMoney(Double.POSITIVE_INFINITY));

        assertEquals(100.0, wallet.getBalance());
        assertEquals(0, wallet.getTransactions().length);
    }

    @Test
    void deductMoneyDecreasesBalanceAndRecordsDebit() {
        Wallet wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);

        wallet.deductMoney(25.50);

        assertEquals(74.50, wallet.getBalance(), 0.0000001);
        Transaction[] transactions = wallet.getTransactions();
        assertEquals(1, transactions.length);
        assertEquals(25.50, transactions[0].getAmount());
        assertFalse(transactions[0].isCreditTransaction());
    }

    @Test
    void deductMoneyAllowsExactAvailableBalance() {
        Wallet wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);

        wallet.deductMoney(100.0);

        assertEquals(0.0, wallet.getBalance());
        assertEquals(1, wallet.getTransactions().length);
    }

    @Test
    void deductMoneyRejectsInsufficientFundsWithoutChangingState() {
        Wallet wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);

        assertThrows(IllegalArgumentException.class, () -> wallet.deductMoney(100.01));

        assertEquals(100.0, wallet.getBalance());
        assertEquals(0, wallet.getTransactions().length);
    }

    @Test
    void deductMoneyRejectsNegativeAndZeroAmountsWithoutChangingState() {
        Wallet wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);

        assertThrows(IllegalArgumentException.class, () -> wallet.deductMoney(-1.0));
        assertThrows(IllegalArgumentException.class, () -> wallet.deductMoney(0.0));

        assertEquals(100.0, wallet.getBalance());
        assertEquals(0, wallet.getTransactions().length);
    }

    @Test
    void transactionArrayGetterReturnsADefensiveCopy() {
        Wallet wallet = new Wallet("alice@upi", 0.0, TEST_CLOCK);
        wallet.addMoney(10.0);

        Transaction[] snapshot = wallet.getTransactions();
        snapshot[0] = null;

        assertArrayEquals(new Transaction[]{wallet.getTransactions()[0]}, wallet.getTransactions());
    }
}
