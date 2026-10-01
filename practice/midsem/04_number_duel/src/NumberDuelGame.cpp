#include "NumberDuelGame.h"

#include <stdexcept>
#include <utility>

NumberDuelGame::NumberDuelGame(Player first, Player second)
    : first_(std::move(first)),
      second_(std::move(second)),
      activePlayer_(0),
      gameOver_(false),
      winner_(-1) {
}

Player& NumberDuelGame::activePlayerReference() {
    return activePlayer_ == 0 ? first_ : second_;
}

const Player& NumberDuelGame::activePlayerReference() const {
    return activePlayer_ == 0 ? first_ : second_;
}

const Player& NumberDuelGame::winnerReference() const {
    return winner_ == 0 ? first_ : second_;
}

Feedback NumberDuelGame::submitGuess(int guess) {
    (void)guess;
    // TODO: implement the use-case and state transition rules.
    return Feedback::TOO_LOW;
}

bool NumberDuelGame::isGameOver() const {
    return gameOver_;
}

std::string NumberDuelGame::activePlayerName() const {
    return activePlayerReference().getName();
}

std::string NumberDuelGame::winnerName() const {
    if (!gameOver_) {
        return "";
    }
    return winnerReference().getName();
}

int NumberDuelGame::winnerScore() const {
    if (!gameOver_) {
        return 0;
    }
    return winnerReference().score();
}
