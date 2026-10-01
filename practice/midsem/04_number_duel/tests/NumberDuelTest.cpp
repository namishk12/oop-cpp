#include <stdexcept>

#include <gtest/gtest.h>

#include "NumberDuelGame.h"
#include "Player.h"

TEST(PlayerConstruction, PreservesIdentityAndTarget) {
    const Player player("Asha", 42);

    EXPECT_EQ(player.getName(), "Asha");
    EXPECT_EQ(player.getTarget(), 42);
    EXPECT_EQ(player.getAttempts(), 0);
}

TEST(PlayerConstruction, RejectsInvalidIdentityOrTarget) {
    EXPECT_THROW(Player("", 42), std::invalid_argument);
    EXPECT_THROW(Player("Asha", 0), std::invalid_argument);
    EXPECT_THROW(Player("Asha", 101), std::invalid_argument);
}

TEST(Player, ClassifiesTooLowAndTooHighGuesses) {
    Player player("Asha", 50);

    EXPECT_EQ(player.evaluateGuess(20), Feedback::TOO_LOW);
    EXPECT_EQ(player.evaluateGuess(80), Feedback::TOO_HIGH);
    EXPECT_EQ(player.getAttempts(), 2);
}

TEST(Player, ClassifiesADirectHitAndCountsIt) {
    Player player("Asha", 50);

    EXPECT_EQ(player.evaluateGuess(50), Feedback::DIRECT_HIT);
    EXPECT_EQ(player.getAttempts(), 1);
}

TEST(Player, RejectsAnInvalidGuessWithoutCountingIt) {
    Player player("Asha", 50);

    EXPECT_THROW(player.evaluateGuess(0), std::invalid_argument);
    EXPECT_THROW(player.evaluateGuess(101), std::invalid_argument);
    EXPECT_EQ(player.getAttempts(), 0);
}

TEST(Player, ComputesANonNegativeScore) {
    Player player("Asha", 50);

    EXPECT_EQ(player.score(), 0);
    player.evaluateGuess(10);
    EXPECT_EQ(player.score(), 0);
    player.evaluateGuess(20);
    EXPECT_EQ(player.score(), 0);
    player.evaluateGuess(50);
    EXPECT_EQ(player.score(), 97);
}

TEST(NumberDuelGame, StartsWithTheFirstPlayerActive) {
    const NumberDuelGame game(Player("Asha", 50), Player("Bala", 75));

    EXPECT_FALSE(game.isGameOver());
    EXPECT_EQ(game.activePlayerName(), "Asha");
    EXPECT_EQ(game.winnerName(), "");
    EXPECT_EQ(game.winnerScore(), 0);
}

TEST(NumberDuelGame, AlternatesAfterNonWinningGuesses) {
    NumberDuelGame game(Player("Asha", 50), Player("Bala", 75));

    EXPECT_EQ(game.submitGuess(20), Feedback::TOO_LOW);
    EXPECT_EQ(game.activePlayerName(), "Bala");
    EXPECT_EQ(game.submitGuess(90), Feedback::TOO_HIGH);
    EXPECT_EQ(game.activePlayerName(), "Asha");
    EXPECT_FALSE(game.isGameOver());
}

TEST(NumberDuelGame, EndsOnADirectHitAndRecordsWinner) {
    NumberDuelGame game(Player("Asha", 50), Player("Bala", 75));

    game.submitGuess(20);
    EXPECT_EQ(game.submitGuess(75), Feedback::DIRECT_HIT);

    EXPECT_TRUE(game.isGameOver());
    EXPECT_EQ(game.winnerName(), "Bala");
    EXPECT_EQ(game.winnerScore(), 99);
}

TEST(NumberDuelGame, RejectsGuessesAfterGameOver) {
    NumberDuelGame game(Player("Asha", 50), Player("Bala", 75));
    game.submitGuess(50);

    EXPECT_THROW(game.submitGuess(75), std::logic_error);
    EXPECT_EQ(game.winnerName(), "Asha");
}
