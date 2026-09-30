#pragma once

class PlayerProfile {
public:
    void addScore(int points);
    void recordWin() noexcept;
    void incrementGamesPlayed() noexcept;

    int getTotalPoints() const noexcept;
    int getTotalWins() const noexcept;
    int getTotalGames() const noexcept;

private:
    int totalPoints = 0;
    int totalWins = 0;
    int totalGames = 0;
};
