#include "ooad/numberduel/NumberDuelGame.h"

#include <exception>
#include <iostream>
#include <string>

int main()
{
    std::string firstName;
    std::string secondName;
    std::cout << "Player 1 name: ";
    std::getline(std::cin, firstName);
    std::cout << "Player 2 name: ";
    std::getline(std::cin, secondName);

    Player first(firstName.empty() ? "Player 1" : firstName);
    Player second(secondName.empty() ? "Player 2" : secondName);
    NumberDuelGame game;
    game.startNewGame(first, second);

    while (!game.isGameOver()) {
        Player* active = game.getActivePlayer();
        int guess = 0;
        std::cout << active->getName() << "'s guess (0-100): ";
        std::cin >> guess;

        try {
            const Feedback feedback = game.processTurn(guess);
            std::cout << displayMessage(feedback) << '\n';
        } catch (const std::exception& error) {
            std::cout << error.what() << '\n';
        }
    }

    if (const GameSummary* summary = game.getGameSummary()) {
        summary->displaySummary();
    }
    return 0;
}
