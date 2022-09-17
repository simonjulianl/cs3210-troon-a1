#ifndef CS3210_A1_A1_A0196678A_A0219768L_PLATFORMUNIT_H
#define CS3210_A1_A1_A0196678A_A0219768L_PLATFORMUNIT_H

#include <mutex>
#include <queue>
#include <utility>
#include "Troon.h"

class Platform;

class WaitingArea {
    /*
     * Multiple producers (from multiple links), 1 Consumer (the Platform attached to this WA)
     */
private:
    struct TroonComparison {
        bool operator()(const Troon *a, const Troon *b) const {
            return a->id > b->id;
        }
    };

    std::priority_queue<Troon *, std::deque<Troon *>, TroonComparison> troonPq;
public:
    string source;
    string destination;
    Platform *nextPlatform = nullptr;

    WaitingArea(string source, string destination) :
            source{std::move(source)},
            destination{std::move(destination)} {};

    void AddTroon(Troon *troon);

    void ProcessWaitingArea();
};

class Link {
public:
    Troon *currentTroon = nullptr;
    WaitingArea *nextWaGreen = nullptr;
    WaitingArea *nextWaYellow = nullptr;
    WaitingArea *nextWaBlue = nullptr;

    size_t currentCounter = 0;

    size_t actualDistance = 0;
    size_t currentDistance = 0;

    string source;
    string destination;

    Link(string source, string destination, size_t distance) : actualDistance{distance}, source{std::move(source)},
                                                               destination{std::move(destination)} {}

    void ProcessLink();

    void AddTroon(Troon *t);

    bool IsNotFree() const;

    bool SafeToGo() const;
};

class Platform {
public:
    Troon *currentTroon = nullptr;
    Link *nextLink = nullptr;

    size_t popularity = 0;
    size_t currentCounter = 0;

    string source;
    string destination;

    Platform(string source, string destination, size_t popularity) : popularity{popularity},
                                                                     source{std::move(source)},
                                                                     destination{std::move(destination)} {};

    void ProcessWaitPlatform();

    void AddTroon(Troon *t);

    bool HasTroon() const;

    void ProcessPushPlatform();
};

#endif //CS3210_A1_A1_A0196678A_A0219768L_PLATFORMUNIT_H
