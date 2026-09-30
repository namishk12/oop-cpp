#include "intro/NumberGuessGame.h"

#include <iostream>
#include <random>

NumberGuessGame::NumberGuessGame()
{
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<int> distribution(1, 100);
    number = distribution(generator);
}

NumberGuessGame::NumberGuessGame(int secretNumber)
    : number(secretNumber)
{
    if (number < 1 || number > 100) {
        number = 1;
    }
}

bool NumberGuessGame::isCorrect(int guess) const noexcept
{
    return guess == number;
}

std::string NumberGuessGame::hint(int guess) const
{
    if (guess < number) {
        return "Too low!";
    }
    if (guess > number) {
        return "Too high!";
    }
    return "Correct!";
}

void NumberGuessGame::play() const
{
    std::cout << "Guess a number from 1 to 100.\n";
    int guess = 0;
    while (!isCorrect(guess)) {
        std::cout << "Make a guess: ";
        std::cin >> guess;
        std::cout << hint(guess) << '\n';
    }
}
