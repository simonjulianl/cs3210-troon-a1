#include "Platform.h"
#include <iostream>

void Platform::ProcessPlatform() {
    int maxCounter = this->popularity + 2;
    if (!this->currentTroon.has_value()) return;

    if (this->currentCounter == maxCounter) {
        this->currentCounter = 0;
        this->nextLink->AddTroon(this->currentTroon.value());
        this->currentTroon = std::nullopt;
    } else {
        this->currentCounter += 1;
    }
}

void Platform::AddTroon(Troon &t) {
    if (this->currentTroon.has_value()) {
        std::string message = "Platform has another troon";
        std::cout << message << std::endl;
        throw std::invalid_argument(message);
    }

    this->currentTroon = t;
    t.setLocation(PLATFORM);
}
