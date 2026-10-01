#ifndef MIDSEM_PLAYER_H
#define MIDSEM_PLAYER_H

#include <string>

#include "Feedback.h"

class Player {
private:
    std::string name_;
    int target_;
    int attempts_;
    bool won_;

public:
    Player(std::string name, int target);

    std::string getName() const;
    int getTarget() const;
    int getAttempts() const;
    Feedback evaluateGuess(int guess);
    int score() const;
};

#endif
