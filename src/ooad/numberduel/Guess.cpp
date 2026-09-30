#include "ooad/numberduel/Guess.h"

Guess::Guess(int value, int attemptNumber)
    : value(value), attemptNumber(attemptNumber)
{
}

int Guess::getValue() const noexcept
{
    return value;
}

int Guess::getAttemptNumber() const noexcept
{
    return attemptNumber;
}
