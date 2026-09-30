#include "ooad/numberduel/Feedback.h"
#include "ooad/numberduel/NumberDuelGame.h"
#include "ooad/numberduel/Player.h"
#include "ooad/numberduel/PlayerProfile.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

TEST(PlayerProfileTest, StartsEmpty)
{
    const PlayerProfile profile;

    EXPECT_EQ(profile.getTotalGames(), 0);
    EXPECT_EQ(profile.getTotalWins(), 0);
    EXPECT_EQ(profile.getTotalPoints(), 0);
}

TEST(PlayerProfileTest, RecordsWinsGamesAndPositiveScore)
{
    PlayerProfile profile;

    profile.addScore(85);
    profile.recordWin();
    profile.incrementGamesPlayed();

    EXPECT_EQ(profile.getTotalPoints(), 85);
    EXPECT_EQ(profile.getTotalWins(), 1);
    EXPECT_EQ(profile.getTotalGames(), 1);
}

TEST(PlayerProfileTest, IgnoresNonPositiveScore)
{
    PlayerProfile profile;
    profile.addScore(90);
    profile.addScore(75);
    profile.addScore(0);
    profile.addScore(-10);

    EXPECT_EQ(profile.getTotalPoints(), 165);
}

TEST(PlayerTest, StartsWithNameAndEmptyMatchState)
{
    const Player player("Anita");

    EXPECT_EQ(player.getName(), "Anita");
    EXPECT_EQ(player.getAttemptCount(), 0);
    EXPECT_FALSE(player.hasSecretTarget());
    EXPECT_EQ(player.getProfile().getTotalGames(), 0);
    EXPECT_TRUE(player.getHistory().getHistory().empty());
}

TEST(PlayerTest, GuessIncrementsAttemptNumber)
{
    Player player("Anita");

    const Guess first = player.makeGuess(50);
    const Guess second = player.makeGuess(30);

    EXPECT_EQ(first.getValue(), 50);
    EXPECT_EQ(first.getAttemptNumber(), 1);
    EXPECT_EQ(second.getValue(), 30);
    EXPECT_EQ(second.getAttemptNumber(), 2);
    EXPECT_EQ(player.getAttemptCount(), 2);
}

TEST(PlayerTest, GuessRejectsValuesOutsideTheGameRange)
{
    Player player("Anita");

    EXPECT_THROW(player.makeGuess(-1), std::invalid_argument);
    EXPECT_THROW(player.makeGuess(101), std::invalid_argument);
    EXPECT_EQ(player.getAttemptCount(), 0);
}

TEST(PlayerTest, ResetClearsMatchStateButKeepsCareerProfile)
{
    Player player("Anita");
    player.makeGuess(50);
    player.getHistory().add(Guess(50, 1), Feedback::TooLow);
    player.getProfile().recordWin();
    player.getProfile().incrementGamesPlayed();

    player.resetForNewGame();

    EXPECT_EQ(player.getAttemptCount(), 0);
    EXPECT_TRUE(player.getHistory().getHistory().empty());
    EXPECT_EQ(player.getProfile().getTotalWins(), 1);
    EXPECT_EQ(player.getProfile().getTotalGames(), 1);
}

class NumberDuelGameTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        anita.setSecretTarget(25);
        vijay.setSecretTarget(70);
        game.startNewGame(anita, vijay);
    }

    NumberDuelGame game;
    Player anita{"Anita"};
    Player vijay{"Vijay"};
};

TEST_F(NumberDuelGameTest, IdentifiesTooHighGuess)
{
    EXPECT_EQ(game.processTurn(80), Feedback::TooHigh);
    EXPECT_EQ(anita.getAttemptCount(), 1);
    EXPECT_FALSE(game.isGameOver());
}

TEST_F(NumberDuelGameTest, IdentifiesTooLowGuess)
{
    EXPECT_EQ(game.processTurn(50), Feedback::TooLow);
    EXPECT_EQ(anita.getAttemptCount(), 1);
    EXPECT_FALSE(game.isGameOver());
}

TEST_F(NumberDuelGameTest, AlternatesTurnsAfterMisses)
{
    EXPECT_EQ(game.getActivePlayer(), &anita);

    game.processTurn(50);
    EXPECT_EQ(game.getActivePlayer(), &vijay);

    game.processTurn(30);
    EXPECT_EQ(game.getActivePlayer(), &anita);
    EXPECT_EQ(vijay.getAttemptCount(), 1);
}

TEST_F(NumberDuelGameTest, DirectHitEndsGameAndAwardsPoints)
{
    game.processTurn(80);
    game.processTurn(10);
    game.processTurn(60);
    game.processTurn(40);
    EXPECT_EQ(game.processTurn(70), Feedback::DirectHit);

    ASSERT_TRUE(game.isGameOver());
    const GameSummary* summary = game.getGameSummary();
    ASSERT_NE(summary, nullptr);
    EXPECT_EQ(summary->getWinnerName(), "Anita");
    EXPECT_EQ(summary->getLoserName(), "Vijay");
    EXPECT_EQ(summary->getAttemptsUsed(), 3);
    EXPECT_EQ(summary->getPointsAwarded(), 97);
    EXPECT_EQ(anita.getProfile().getTotalPoints(), 97);
    EXPECT_EQ(anita.getProfile().getTotalWins(), 1);
    EXPECT_EQ(anita.getProfile().getTotalGames(), 1);
    EXPECT_EQ(vijay.getProfile().getTotalGames(), 1);
}

TEST_F(NumberDuelGameTest, CannotPlayAfterGameEnds)
{
    game.processTurn(70);

    EXPECT_THROW(game.processTurn(50), std::logic_error);
}

TEST(FeedbackTest, ProvidesDisplayMessages)
{
    EXPECT_NE(displayMessage(Feedback::TooHigh).find("Too High"), std::string::npos);
    EXPECT_NE(displayMessage(Feedback::TooLow).find("Too Low"), std::string::npos);
    EXPECT_NE(displayMessage(Feedback::DirectHit).find("Direct Hit"), std::string::npos);
}
