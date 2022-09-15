#include "PlatformUnit.h"
#include <iostream>

void Platform::ProcessPlatform() {
    size_t maxCounter = popularity + 2;
    if (!currentTroon.has_value()) return;

    if (currentCounter == maxCounter) {
        currentCounter = 0;
        nextLink->AddTroon(currentTroon.value());
        currentTroon = std::nullopt;
    } else {
        currentCounter += 1;
    }
}

void Platform::AddTroon(Troon &t) {
    if (currentTroon.has_value()) {
        std::string message = "Platform has another troon";
        std::cout << message << std::endl;
        throw std::invalid_argument(message);
    }

    currentTroon = t;
    t.setLocation(PLATFORM);
}

void Link::ProcessLink() {
    if (!currentTroon.has_value()) return;

    if (currentDistance == actualDistance) {
        nextWa->AddTroon(currentTroon.value());
        currentTroon = std::nullopt;
    } else {
        currentDistance++;
    }
}

void Link::AddTroon(Troon &t) {
    if (currentTroon.has_value()) {
        std::string message = "Link has another troon";
        std::cout << message << std::endl;
        throw std::invalid_argument(message);
    }

    currentTroon = t;
    currentTroon->setLocation(LINK);
}

void WaitingArea::AddTroon(Troon &troon) {
    troon.setSourceDestination(source, destination);
    troon.setLocation(WAITING_AREA);

    mtx->lock();
    troonPq.push(troon);
    mtx->unlock();
}

bool WaitingArea::IsEmpty() const {
    return (troonPq).empty();
}

void WaitingArea::ProcessWaitingArea() {
    if (IsEmpty()) return;

    Troon top = troonPq.top();
    nextPlatform->AddTroon(top);
    troonPq.pop();
}
