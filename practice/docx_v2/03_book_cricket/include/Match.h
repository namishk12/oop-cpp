#ifndef DOCX_V2_MATCH_H
#define DOCX_V2_MATCH_H

#include <string>
#include <vector>

#include "Innings.h"

enum class MatchResult {
    NotPlayed,
    FirstInningsWins,
    SecondInningsWins,
    Tie
};

class Match {
private:
    bool played_;
    Innings inningsOne_;
    Innings inningsTwo_;

public:
    Match(std::string batsmanOne,
          std::string batsmanTwo,
          int overs,
          bool batsmanOneStarts);

    void play(const std::vector<int>& pagesForFirstInnings,
              const std::vector<int>& pagesForSecondInnings);

    bool isPlayed() const;
    const Innings& inningsOne() const;
    const Innings& inningsTwo() const;
    MatchResult result() const;
    std::string winnerName() const;
};

#endif
