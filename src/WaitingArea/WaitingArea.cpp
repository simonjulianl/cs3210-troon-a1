#include "WaitingArea.h"
#include <iostream>
#include <string>

void WaitingArea::AddTroon(const Troon &troon) {
    this->mtx.lock();
    this->troonPq.push(troon);
    this->mtx.unlock();
}

Troon const &WaitingArea::GetFrontTroon() {
    if (this->IsEmpty()) {
        std::string message = "Waiting Area is Empty";
        std::cout << message << std::endl;
        throw std::invalid_argument(message);
    }

    Troon const &top = this->troonPq.top();
    troonPq.pop();
    return top;
}

bool WaitingArea::IsEmpty() {
    return (this->troonPq).empty();
}
