import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

class TransactionTest {

    @Test
    void storesAllTransactionDetails() {
        LocalDateTime timestamp = LocalDateTime.of(2026, 1, 2, 10, 15);

        Transaction transaction = new Transaction("txn-1", 125.50, true, timestamp);

        assertEquals("txn-1", transaction.getTransactionId());
        assertEquals(125.50, transaction.getAmount());
        assertTrue(transaction.isCreditTransaction());
        assertEquals(timestamp, transaction.getTimestamp());
    }

    @Test
    void supportsDebitTransactions() {
        Transaction transaction = new Transaction("txn-2", 40.0, false);

        assertFalse(transaction.isCreditTransaction());
        assertNotNull(transaction.getTimestamp());
    }

    @Test
    void rejectsNegativeAmounts() {
        assertThrows(IllegalArgumentException.class,
                () -> new Transaction("txn-3", -1.0, true, LocalDateTime.now()));
    }

    @Test
    void rejectsNonFiniteAndZeroAmounts() {
        assertThrows(IllegalArgumentException.class,
                () -> new Transaction("txn-4", 0.0, true, LocalDateTime.now()));
        assertThrows(IllegalArgumentException.class,
                () -> new Transaction("txn-5", Double.NaN, true, LocalDateTime.now()));
        assertThrows(IllegalArgumentException.class,
                () -> new Transaction("txn-6", Double.POSITIVE_INFINITY, true, LocalDateTime.now()));
    }
}
