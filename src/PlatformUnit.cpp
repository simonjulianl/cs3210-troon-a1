#include "PlatformUnit.h"
#include <iostream>
#include <omp.h>

using namespace std;

void Platform::ProcessWaitPlatform() {
    if (HasTroon()) {
        currentCounter += 1;
    }
}


void Platform::ProcessPushPlatform() {
    size_t maxCounter = popularity + 2;
    bool isReadyToGo = currentCounter >= maxCounter;

    if (!currentTroon || !isReadyToGo || nextLink->IsNotFree() || !nextLink->SafeToGo()) return;

    currentCounter = 0;
    nextLink->AddTroon(currentTroon);
    currentTroon = nullptr;
}

void Platform::AddTroon(Troon *t) {
    if (currentTroon) {
        std::string message = "Platform has another troon";
        std::cout << message << std::endl;
        throw std::invalid_argument(message);
    }

    currentTroon = t;
    t->setLocation(PLATFORM);
}

bool Platform::HasTroon() const {
    return currentTroon != nullptr;
}

void Link::ProcessLink() {
    if (!currentTroon) {
        currentCounter++;
        return;
    }

    if (currentDistance == (actualDistance - 1)) {
        switch (currentTroon->line) {
            case g:
                nextWaGreen->AddTroon(currentTroon);
                break;
            case y:
                nextWaYellow->AddTroon(currentTroon);
                break;
            case b:
                nextWaBlue->AddTroon(currentTroon);
                break;
        }
        currentTroon = nullptr;
        currentCounter = 0;
    } else {
        currentDistance++;
    }
}

void Link::AddTroon(Troon *t) {
    if (currentTroon) {
        std::string message = "Link has another troon";
        std::cout << message << std::endl;
        throw std::invalid_argument(message);
    }

    currentTroon = t;
    currentTroon->setLocation(LINK);
}

bool Link::IsNotFree() const {
    return currentTroon != nullptr;
}

bool Link::SafeToGo() const {
    return currentCounter >= 1;
}

void WaitingArea::AddTroon(Troon *troon) {
    troon->setSourceDestination(source, destination);
    troon->setLocation(WAITING_AREA);

#pragma omp critical
    troonPq.push(troon);
}

void WaitingArea::ProcessWaitingArea() {
    if (troonPq.empty() || nextPlatform->HasTroon()) return;

    Troon *top = troonPq.top();
    nextPlatform->AddTroon(top);
    troonPq.pop();
}
