#pragma once

#include "ooad/numberduel/Guess.h"
#include "ooad/numberduel/GuessHistory.h"
#include "ooad/numberduel/PlayerProfile.h"

#include <string>

class Player {
public:
    explicit Player(std::string name);

    Guess makeGuess(int value);
    void resetForNewGame() noexcept;
    void setSecretTarget(int target);

    const std::string& getName() const noexcept;
    int getSecretTarget() const noexcept;
    int getAttemptCount() const noexcept;
    bool hasSecretTarget() const noexcept;
    PlayerProfile& getProfile() noexcept;
    const PlayerProfile& getProfile() const noexcept;
    GuessHistory& getHistory() noexcept;
    const GuessHistory& getHistory() const noexcept;

private:
    std::string name;
    int secretTarget = 0;
    int attemptCount = 0;
    bool targetAssigned = false;
    PlayerProfile profile;
    GuessHistory history;
};
