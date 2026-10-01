#include "BookCricketRules.h"

#include <stdexcept>

DeliveryResult BookCricketRules::fromPage(int pageNumber) {
    (void)pageNumber;
    // TODO: map the last digit to the table in the question.
    return {DeliveryOutcome::NoEffect, 0};
}
