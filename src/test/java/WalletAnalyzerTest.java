import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.time.Clock;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneOffset;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

class WalletAnalyzerTest {

    private static final double DELTA = 0.0000001;
    private static final Clock TEST_CLOCK = Clock.fixed(
            Instant.parse("2026-01-01T12:00:00Z"), ZoneOffset.UTC);
    private Wallet wallet;
    private WalletAnalyzer analyzer;

    @BeforeEach
    void setUp() {
        wallet = new Wallet("alice@upi", 100.0, TEST_CLOCK);
        analyzer = new WalletAnalyzer(wallet);
    }

    @Test
    void totalAmountCreditedReturnsAllCredits() {
        wallet.addMoney(25.0);
        wallet.deductMoney(10.0);
        wallet.addMoney(50.0);

        assertEquals(75.0, analyzer.totalAmountCredited(), DELTA);
    }

    @Test
    void totalAmountCreditedIsZeroWhenThereAreNoCredits() {
        wallet.deductMoney(20.0);

        assertEquals(0.0, analyzer.totalAmountCredited(), DELTA);
    }

    @Test
    void totalAmountCreditedDoesNotCountOpeningBalance() {
        assertEquals(0.0, analyzer.totalAmountCredited(), DELTA);
    }

    @Test
    void totalAmountCreditedReflectsLaterTransactions() {
        wallet.addMoney(10.0);
        assertEquals(10.0, analyzer.totalAmountCredited(), DELTA);

        wallet.addMoney(15.0);
        assertEquals(25.0, analyzer.totalAmountCredited(), DELTA);
    }

    @Test
    void totalAmountDebitedReturnsAllDebits() {
        wallet.addMoney(25.0);
        wallet.deductMoney(10.0);
        wallet.deductMoney(15.0);

        assertEquals(25.0, analyzer.totalAmountDebited(), DELTA);
    }

    @Test
    void totalAmountDebitedIsZeroWhenThereAreNoDebits() {
        wallet.addMoney(20.0);

        assertEquals(0.0, analyzer.totalAmountDebited(), DELTA);
    }

    @Test
    void totalAmountDebitedDoesNotCountOpeningBalance() {
        assertEquals(0.0, analyzer.totalAmountDebited(), DELTA);
    }

    @Test
    void totalAmountDebitedReflectsLaterTransactions() {
        wallet.deductMoney(10.0);
        assertEquals(10.0, analyzer.totalAmountDebited(), DELTA);

        wallet.deductMoney(15.0);
        assertEquals(25.0, analyzer.totalAmountDebited(), DELTA);
    }

    @Test
    void expenditureBetweenIncludesDebitsAtBothBoundaries() {
        wallet.deductMoney(10.0);
        LocalDateTime timestamp = wallet.getTransactions()[0].getTimestamp();
        wallet.addMoney(20.0);
        wallet.deductMoney(15.0);

        assertEquals(25.0, analyzer.expenditureBetween(
                timestamp, timestamp), DELTA);
    }

    @Test
    void expenditureBetweenExcludesCredits() {
        wallet.addMoney(50.0);
        LocalDateTime start = wallet.getTransactions()[0].getTimestamp();

        assertEquals(0.0, analyzer.expenditureBetween(
                start, start), DELTA);
    }

    @Test
    void expenditureBetweenReturnsZeroForAnOutsideRange() {
        wallet.deductMoney(10.0);
        LocalDateTime timestamp = wallet.getTransactions()[0].getTimestamp();

        assertEquals(0.0, analyzer.expenditureBetween(
                timestamp.minusDays(2), timestamp.minusDays(1)), DELTA);
    }

    @Test
    void expenditureBetweenRejectsAnInvalidDateRange() {
        LocalDateTime start = LocalDateTime.of(2026, 1, 2, 0, 0);
        LocalDateTime end = start.minusMinutes(1);

        assertThrows(IllegalArgumentException.class,
                () -> analyzer.expenditureBetween(start, end));
    }
}
