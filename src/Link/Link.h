#ifndef CS3210_A1_A1_A0196678A_A0219768L_LINK_H
#define CS3210_A1_A1_A0196678A_A0219768L_LINK_H


#include <optional>
#include "../Train/Troon.h"
#include "../WaitingArea/WaitingArea.h"

using std::optional;

class Link {
public:
    optional<Troon> currentTroon = std::nullopt;
    optional<WaitingArea> nextWa = std::nullopt;

    int actualDistance;
    int currentDistance = 0;

    explicit Link(int distance) : actualDistance{distance} {}

    void ProcessLink();

    void AddTroon(Troon &t);
};


#endif //CS3210_A1_A1_A0196678A_A0219768L_LINK_H
