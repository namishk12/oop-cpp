#include "ooad/numberduel/Player.h"

#include <stdexcept>

Player::Player(std::string name)
    : name(name)
{
}

Guess Player::makeGuess(int value)
{
    if (value < 0 || value > 100) {
        throw std::invalid_argument("Guess must be between 0 and 100 inclusive");
    }
    ++attemptCount;
    return Guess(value, attemptCount);
}

void Player::resetForNewGame() noexcept
{
    attemptCount = 0;
    history.clear();
}

void Player::setSecretTarget(int target)
{
    if (target < 0 || target > 100) {
        throw std::invalid_argument("Secret target must be between 0 and 100 inclusive");
    }
    secretTarget = target;
    targetAssigned = true;
}

const std::string& Player::getName() const noexcept
{
    return name;
}

int Player::getSecretTarget() const noexcept
{
    return secretTarget;
}

int Player::getAttemptCount() const noexcept
{
    return attemptCount;
}

bool Player::hasSecretTarget() const noexcept
{
    return targetAssigned;
}

PlayerProfile& Player::getProfile() noexcept
{
    return profile;
}

const PlayerProfile& Player::getProfile() const noexcept
{
    return profile;
}

GuessHistory& Player::getHistory() noexcept
{
    return history;
}

const GuessHistory& Player::getHistory() const noexcept
{
    return history;
}
