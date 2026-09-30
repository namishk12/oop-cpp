#pragma once

#include <string>

class NumberGuessGame {
public:
    NumberGuessGame();
    explicit NumberGuessGame(int secretNumber);

    bool isCorrect(int guess) const noexcept;
    std::string hint(int guess) const;
    void play() const;

private:
    int number;
};
