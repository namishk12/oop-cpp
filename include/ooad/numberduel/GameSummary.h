#pragma once

#include <string>

class GameSummary {
public:
    GameSummary();
    GameSummary(std::string winnerName,
                std::string loserName,
                int attemptsUsed,
                int pointsAwarded);

    const std::string& getWinnerName() const noexcept;
    const std::string& getLoserName() const noexcept;
    int getAttemptsUsed() const noexcept;
    int getPointsAwarded() const noexcept;
    void displaySummary() const;

private:
    std::string winnerName;
    std::string loserName;
    int attemptsUsed;
    int pointsAwarded;
};
