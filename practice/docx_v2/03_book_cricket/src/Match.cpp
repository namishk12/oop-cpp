#include "Match.h"

#include <stdexcept>
#include <utility>

Match::Match(std::string batsmanOne,
             std::string batsmanTwo,
             int overs,
             bool batsmanOneStarts)
    : played_(false),
      inningsOne_(batsmanOneStarts ? batsmanOne : batsmanTwo, overs),
      inningsTwo_(batsmanOneStarts ? batsmanTwo : batsmanOne, overs) {
    // TODO: validate both names and the number of overs.
}

void Match::play(const std::vector<int>& pagesForFirstInnings,
                 const std::vector<int>& pagesForSecondInnings) {
    (void)pagesForFirstInnings;
    (void)pagesForSecondInnings;
    // TODO: feed both innings until each is complete, then mark the match played.
}

bool Match::isPlayed() const {
    return played_;
}

const Innings& Match::inningsOne() const {
    return inningsOne_;
}

const Innings& Match::inningsTwo() const {
    return inningsTwo_;
}

MatchResult Match::result() const {
    // TODO: compare scores after play().
    return MatchResult::NotPlayed;
}

std::string Match::winnerName() const {
    // TODO: return the winning innings' batsman, or an empty string for no win.
    return "";
}
