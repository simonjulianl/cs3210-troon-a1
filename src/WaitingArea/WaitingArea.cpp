#include "WaitingArea.h"

void WaitingArea::AddTroon(Troon &troon) {
    troon.setSourceDestination(this->source, this->destination);
    troon.setLocation(WAITING_AREA);

    this->mtx.lock();
    this->troonPq.push(troon);
    this->mtx.unlock();
}

bool WaitingArea::IsEmpty() {
    return (this->troonPq).empty();
}

void WaitingArea::ProcessWaitingArea() {
    if (this->IsEmpty()) return;

    Troon top = this->troonPq.top();
    this->nextPlatform.AddTroon(top);
    this->troonPq.pop();
}
