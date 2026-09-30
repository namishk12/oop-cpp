#include "ooad/numberduel/GameSummary.h"

#include <iostream>

GameSummary::GameSummary()
    : attemptsUsed(0), pointsAwarded(0)
{
}

GameSummary::GameSummary(std::string winnerName,
                         std::string loserName,
                         int attemptsUsed,
                         int pointsAwarded)
    : winnerName(winnerName),
      loserName(loserName),
      attemptsUsed(attemptsUsed),
      pointsAwarded(pointsAwarded)
{
}

const std::string& GameSummary::getWinnerName() const noexcept
{
    return winnerName;
}

const std::string& GameSummary::getLoserName() const noexcept
{
    return loserName;
}

int GameSummary::getAttemptsUsed() const noexcept
{
    return attemptsUsed;
}

int GameSummary::getPointsAwarded() const noexcept
{
    return pointsAwarded;
}

void GameSummary::displaySummary() const
{
    std::cout << "\n=================================\n"
              << "          GAME SUMMARY           \n"
              << "=================================\n"
              << "Winner: " << winnerName << '\n'
              << "Attempts Taken: " << attemptsUsed << '\n'
              << "Points Awarded: " << pointsAwarded << " pts\n"
              << "Loser: " << loserName << " (0 pts)\n"
              << "=================================\n\n";
}
