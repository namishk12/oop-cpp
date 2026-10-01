#ifndef DOCX_V2_BOOK_CRICKET_RULES_H
#define DOCX_V2_BOOK_CRICKET_RULES_H

#include "Delivery.h"

class BookCricketRules {
public:
    static DeliveryResult fromPage(int pageNumber);
};

#endif
