#pragma once

#include "ooad/numberduel/Feedback.h"
#include "ooad/numberduel/GameSummary.h"
#include "ooad/numberduel/Player.h"

class NumberDuelGame {
public:
    void startNewGame(Player& player1, Player& player2);
    Feedback processTurn(int guessedValue);

    bool isGameOver() const noexcept;
    Player* getActivePlayer() const noexcept;
    Player* getOpponentPlayer() const noexcept;
    const GameSummary* getGameSummary() const noexcept;

private:
    Feedback evaluate(const Guess& guess, int target) const noexcept;
    void switchTurn() noexcept;
    GameSummary concludeGame();

    Player* player1 = nullptr;
    Player* player2 = nullptr;
    Player* activePlayer = nullptr;
    Player* opponentPlayer = nullptr;
    bool gameOver = false;
    bool summaryAvailable = false;
    GameSummary summary;
};
