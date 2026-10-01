#include "Innings.h"

#include "BookCricketRules.h"

#include <stdexcept>
#include <utility>

Innings::Innings(std::string batsman, int overs)
    : batsman_(std::move(batsman)),
      overs_(overs),
      runs_(0),
      legalBalls_(0),
      out_(false) {
    // TODO: reject an empty batsman name or non-positive overs.
}

void Innings::deliver(int pageNumber) {
    (void)pageNumber;
    // TODO: evaluate the page and update state according to the delivery rules.
}

bool Innings::isComplete() const {
    return out_ || legalBalls_ >= overs_ * 6;
}

bool Innings::isOut() const {
    return out_;
}

int Innings::runs() const {
    return runs_;
}

int Innings::legalBalls() const {
    return legalBalls_;
}

std::string Innings::batsman() const {
    return batsman_;
}
