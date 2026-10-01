#ifndef MIDSEM_NUMBER_DUEL_GAME_H
#define MIDSEM_NUMBER_DUEL_GAME_H

#include <string>

#include "Player.h"

class NumberDuelGame {
private:
    Player first_;
    Player second_;
    int activePlayer_;
    bool gameOver_;
    int winner_;

    Player& activePlayerReference();
    const Player& activePlayerReference() const;
    const Player& winnerReference() const;

public:
    NumberDuelGame(Player first, Player second);

    Feedback submitGuess(int guess);
    bool isGameOver() const;
    std::string activePlayerName() const;
    std::string winnerName() const;
    int winnerScore() const;
};

#endif
