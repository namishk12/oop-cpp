#include <stdexcept>
#include <vector>

#include <gtest/gtest.h>

#include "BookCricketRules.h"
#include "Innings.h"
#include "Match.h"

TEST(BookCricketRules, ConvertsRunDigits) {
    EXPECT_EQ(BookCricketRules::fromPage(241).outcome, DeliveryOutcome::Runs);
    EXPECT_EQ(BookCricketRules::fromPage(241).runs, 1);
    EXPECT_EQ(BookCricketRules::fromPage(356).runs, 6);
    EXPECT_EQ(BookCricketRules::fromPage(124).runs, 4);
}

TEST(BookCricketRules, ConvertsWideDigit) {
    const DeliveryResult result = BookCricketRules::fromPage(125);

    EXPECT_EQ(result.outcome, DeliveryOutcome::Wide);
    EXPECT_EQ(result.runs, 1);
}

TEST(BookCricketRules, ConvertsNoEffectDigits) {
    EXPECT_EQ(BookCricketRules::fromPage(837).outcome, DeliveryOutcome::NoEffect);
    EXPECT_EQ(BookCricketRules::fromPage(837).runs, 0);
    EXPECT_EQ(BookCricketRules::fromPage(129).outcome, DeliveryOutcome::NoEffect);
}

TEST(BookCricketRules, ConvertsOutDigits) {
    EXPECT_EQ(BookCricketRules::fromPage(108).outcome, DeliveryOutcome::Out);
    EXPECT_EQ(BookCricketRules::fromPage(108).runs, 0);
    EXPECT_EQ(BookCricketRules::fromPage(0).outcome, DeliveryOutcome::Out);
}

TEST(BookCricketRules, RejectsNegativePages) {
    EXPECT_THROW(BookCricketRules::fromPage(-1), std::invalid_argument);
}

TEST(Innings, CountsRunsAndLegalBalls) {
    Innings innings("Asha", 1);

    innings.deliver(241);
    innings.deliver(356);

    EXPECT_EQ(innings.runs(), 7);
    EXPECT_EQ(innings.legalBalls(), 2);
    EXPECT_FALSE(innings.isOut());
}

TEST(Innings, CountsAWideAsARunButNotALegalBall) {
    Innings innings("Asha", 1);

    innings.deliver(125);

    EXPECT_EQ(innings.runs(), 1);
    EXPECT_EQ(innings.legalBalls(), 0);
    EXPECT_FALSE(innings.isComplete());
}

TEST(Innings, EndsWhenTheBatsmanIsOut) {
    Innings innings("Asha", 2);

    innings.deliver(108);

    EXPECT_TRUE(innings.isOut());
    EXPECT_TRUE(innings.isComplete());
    EXPECT_EQ(innings.legalBalls(), 1);
}

TEST(Innings, EndsAfterSixLegalBallsInOneOver) {
    Innings innings("Asha", 1);

    innings.deliver(837);
    innings.deliver(837);
    innings.deliver(837);
    innings.deliver(837);
    innings.deliver(837);
    innings.deliver(837);

    EXPECT_TRUE(innings.isComplete());
    EXPECT_EQ(innings.legalBalls(), 6);
}

TEST(Innings, RejectsDeliveriesAfterCompletion) {
    Innings innings("Asha", 1);
    innings.deliver(108);

    EXPECT_THROW(innings.deliver(241), std::logic_error);
}

TEST(Match, StartsWithTheSelectedBatsman) {
    const Match match("Asha", "Bala", 1, false);

    EXPECT_FALSE(match.isPlayed());
    EXPECT_EQ(match.inningsOne().batsman(), "Bala");
    EXPECT_EQ(match.inningsTwo().batsman(), "Asha");
    EXPECT_EQ(match.result(), MatchResult::NotPlayed);
}

TEST(Match, ReportsTheWinningSecondInnings) {
    Match match("Asha", "Bala", 1, true);
    const std::vector<int> firstPages{241, 837, 837, 837, 837, 837};
    const std::vector<int> secondPages{356, 837, 837, 837, 837, 837};

    match.play(firstPages, secondPages);

    EXPECT_TRUE(match.isPlayed());
    EXPECT_EQ(match.result(), MatchResult::SecondInningsWins);
    EXPECT_EQ(match.winnerName(), "Bala");
}

TEST(Match, ReportsATie) {
    Match match("Asha", "Bala", 1, true);
    const std::vector<int> pages{108};

    match.play(pages, pages);

    EXPECT_EQ(match.result(), MatchResult::Tie);
    EXPECT_EQ(match.winnerName(), "");
}

TEST(Match, RejectsPlayingTwice) {
    Match match("Asha", "Bala", 1, true);
    const std::vector<int> pages{108};
    match.play(pages, pages);

    EXPECT_THROW(match.play(pages, pages), std::logic_error);
}
