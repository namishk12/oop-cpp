#pragma once

#include "ooad/numberduel/Feedback.h"
#include "ooad/numberduel/Guess.h"

#include <vector>

struct HistoryEntry {
    Guess guess;
    Feedback feedback;
};

class GuessHistory {
public:
    void add(const Guess& guess, Feedback feedback);
    const std::vector<HistoryEntry>& getHistory() const noexcept;
    void clear() noexcept;

private:
    std::vector<HistoryEntry> entries;
};
