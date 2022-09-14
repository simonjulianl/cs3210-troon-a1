#ifndef CS3210_A1_A1_A0196678A_A0219768L_WAITINGAREA_H
#define CS3210_A1_A1_A0196678A_A0219768L_WAITINGAREA_H

#include <mutex>
#include <queue>
#include "../Train/Troon.h"

class WaitingArea {
    /*
     * Multiple producers (from multiple links), 1 Consumer (the Platform attached to this WA)
     */
private:
    std::mutex mtx;
    std::priority_queue<Troon> troonPq;
public:
    WaitingArea() = default;

    void AddTroon(const Troon &troon);

    Troon const &GetFrontTroon();

    bool IsEmpty();
};


#endif //CS3210_A1_A1_A0196678A_A0219768L_WAITINGAREA_H
