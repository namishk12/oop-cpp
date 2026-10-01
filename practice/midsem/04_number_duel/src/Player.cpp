#include "Player.h"

#include <stdexcept>
#include <utility>

Player::Player(std::string name, int target)
    : name_(std::move(name)), target_(target), attempts_(0), won_(false) {
    // TODO: reject an empty name or target outside [1, 100].
}

std::string Player::getName() const {
    return name_;
}

int Player::getTarget() const {
    return target_;
}

int Player::getAttempts() const {
    return attempts_;
}

Feedback Player::evaluateGuess(int guess) {
    (void)guess;
    // TODO: validate the guess, increment attempts, and classify it.
    return Feedback::TOO_LOW;
}

int Player::score() const {
    // TODO: return max(0, 100 - attempts_) after a winning guess.
    return 0;
}
