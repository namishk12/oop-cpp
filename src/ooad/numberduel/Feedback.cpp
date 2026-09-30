#include "ooad/numberduel/Feedback.h"

std::string displayMessage(Feedback feedback)
{
    switch (feedback) {
    case Feedback::TooHigh:
        return "Too High! Try a smaller number.";
    case Feedback::TooLow:
        return "Too Low! Try a larger number.";
    case Feedback::DirectHit:
        return "Direct Hit! Congratulations, you guessed the number!";
    }
    return "Unknown feedback";
}
