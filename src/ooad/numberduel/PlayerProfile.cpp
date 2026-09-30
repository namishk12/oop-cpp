#include "ooad/numberduel/PlayerProfile.h"

void PlayerProfile::addScore(int points)
{
    if (points > 0) {
        totalPoints += points;
    }
}

void PlayerProfile::recordWin() noexcept
{
    ++totalWins;
}

void PlayerProfile::incrementGamesPlayed() noexcept
{
    ++totalGames;
}

int PlayerProfile::getTotalPoints() const noexcept
{
    return totalPoints;
}

int PlayerProfile::getTotalWins() const noexcept
{
    return totalWins;
}

int PlayerProfile::getTotalGames() const noexcept
{
    return totalGames;
}
