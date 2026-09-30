#pragma once

#include <string>

enum class Feedback {
    TooHigh,
    TooLow,
    DirectHit
};

std::string displayMessage(Feedback feedback);
