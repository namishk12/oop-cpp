#include "ooad/numberduel/GuessHistory.h"

void GuessHistory::add(const Guess& guess, Feedback feedback)
{
    entries.push_back({guess, feedback});
}

const std::vector<HistoryEntry>& GuessHistory::getHistory() const noexcept
{
    return entries;
}

void GuessHistory::clear() noexcept
{
    entries.clear();
}
