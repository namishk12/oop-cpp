#include "ooad/numberduel/NumberDuelGame.h"

#include <cstdlib>
#include <stdexcept>

void NumberDuelGame::startNewGame(Player& firstPlayer, Player& secondPlayer)
{
    player1 = &firstPlayer;
    player2 = &secondPlayer;
    gameOver = false;
    summaryAvailable = false;

    player1->resetForNewGame();
    player2->resetForNewGame();

    if (!player1->hasSecretTarget()) {
        player1->setSecretTarget(std::rand() % 101);
    }
    if (!player2->hasSecretTarget()) {
        player2->setSecretTarget(std::rand() % 101);
    }

    activePlayer = player1;
    opponentPlayer = player2;
}

Feedback NumberDuelGame::processTurn(int guessedValue)
{
    if (gameOver) {
        throw std::logic_error("Game is already over. Start a new game to play.");
    }
    if (activePlayer == nullptr || opponentPlayer == nullptr) {
        throw std::logic_error("Start a game before processing turns");
    }

    const Guess currentGuess = activePlayer->makeGuess(guessedValue);
    const Feedback feedback = evaluate(currentGuess, opponentPlayer->getSecretTarget());
    activePlayer->getHistory().add(currentGuess, feedback);

    if (feedback == Feedback::DirectHit) {
        gameOver = true;
        summary = concludeGame();
        summaryAvailable = true;
    } else {
        switchTurn();
    }

    return feedback;
}

bool NumberDuelGame::isGameOver() const noexcept
{
    return gameOver;
}

Player* NumberDuelGame::getActivePlayer() const noexcept
{
    return activePlayer;
}

Player* NumberDuelGame::getOpponentPlayer() const noexcept
{
    return opponentPlayer;
}

const GameSummary* NumberDuelGame::getGameSummary() const noexcept
{
    return summaryAvailable ? &summary : nullptr;
}

Feedback NumberDuelGame::evaluate(const Guess& guess, int target) const noexcept
{
    if (guess.getValue() > target) {
        return Feedback::TooHigh;
    }
    if (guess.getValue() < target) {
        return Feedback::TooLow;
    }
    return Feedback::DirectHit;
}

void NumberDuelGame::switchTurn() noexcept
{
    Player* temporary = activePlayer;
    activePlayer = opponentPlayer;
    opponentPlayer = temporary;
}

GameSummary NumberDuelGame::concludeGame()
{
    const int attempts = activePlayer->getAttemptCount();
    const int winnerScore = attempts < 100 ? 100 - attempts : 0;

    activePlayer->getProfile().addScore(winnerScore);
    activePlayer->getProfile().recordWin();
    activePlayer->getProfile().incrementGamesPlayed();
    opponentPlayer->getProfile().incrementGamesPlayed();

    return GameSummary(activePlayer->getName(),
                       opponentPlayer->getName(),
                       attempts,
                       winnerScore);
}
