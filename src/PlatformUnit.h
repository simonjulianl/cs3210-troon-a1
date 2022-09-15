#ifndef CS3210_A1_A1_A0196678A_A0219768L_PLATFORMUNIT_H
#define CS3210_A1_A1_A0196678A_A0219768L_PLATFORMUNIT_H

#include <optional>
#include <mutex>
#include <queue>
#include <utility>
#include <optional>
#include "Troon.h"

using std::optional;

class Platform;

class WaitingArea {
    /*
     * Multiple producers (from multiple links), 1 Consumer (the Platform attached to this WA)
     */
private:
    std::mutex *mtx;
    std::priority_queue<Troon> troonPq;
public:
    string source;
    string destination;
    Platform *nextPlatform = nullptr;

    WaitingArea(string source, string destination, std::mutex *m) : mtx{m},
                                                                    source{std::move(source)},
                                                                    destination{std::move(destination)} {};

    void AddTroon(Troon &troon);

    bool IsEmpty() const;

    void ProcessWaitingArea();
};

class Link {
public:
    optional<Troon> currentTroon = std::nullopt;
    WaitingArea *nextWa = nullptr;

    size_t actualDistance = 0;
    size_t currentDistance = 0;

    explicit Link(size_t distance) : actualDistance{distance} {}

    void ProcessLink();

    void AddTroon(Troon &t);
};

class Platform {
public:
    optional<Troon> currentTroon = std::nullopt;
    Link *nextLink = nullptr;

    size_t popularity = 0;
    size_t currentCounter = 0;

    explicit Platform(size_t popularity) : popularity{popularity} {};

    void ProcessPlatform();

    void AddTroon(Troon &t);
};

#endif //CS3210_A1_A1_A0196678A_A0219768L_PLATFORMUNIT_H
