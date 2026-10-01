#ifndef DOCX_V2_DELIVERY_H
#define DOCX_V2_DELIVERY_H

enum class DeliveryOutcome {
    Runs,
    Wide,
    NoEffect,
    Out
};

struct DeliveryResult {
    DeliveryOutcome outcome;
    int runs;
};

#endif
