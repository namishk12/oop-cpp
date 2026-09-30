#pragma once

class Guess {
public:
    Guess(int value, int attemptNumber);

    int getValue() const noexcept;
    int getAttemptNumber() const noexcept;

private:
    int value;
    int attemptNumber;
};
