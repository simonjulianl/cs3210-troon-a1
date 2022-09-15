#ifndef CS3210_A1_A1_A0196678A_A0219768L_WAITINGAREA_H
#define CS3210_A1_A1_A0196678A_A0219768L_WAITINGAREA_H

#include <mutex>
#include <queue>
#include <utility>
#include <optional>
#include "../Train/Troon.h"
#include "../Platform/Platform.h"

using namespace std::optional;

class WaitingArea {
    /*
     * Multiple producers (from multiple links), 1 Consumer (the Platform attached to this WA)
     */
private:
    std::mutex mtx;
    std::priority_queue<Troon> troonPq;
public:
    string source;
    string destination;
    optional<Platform> nextPlatform = std::nullopt;

    WaitingArea(string source, string destination) : source{std::move(source)},
                                                     destination{std::move(destination)} {};

    void AddTroon(Troon &troon);

    bool IsEmpty();

    void ProcessWaitingArea();
};


#endif //CS3210_A1_A1_A0196678A_A0219768L_WAITINGAREA_H
