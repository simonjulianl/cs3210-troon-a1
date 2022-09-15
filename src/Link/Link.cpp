#include "Link.h"
#include <iostream>

void Link::ProcessLink() {
    if (!this->currentTroon.has_value()) return;

    if (this->currentDistance == this->actualDistance) {
        this->nextWa->AddTroon(this->currentTroon.value());
        this->currentTroon = std::nullopt;
    } else {
        this->currentDistance++;
    }
}

void Link::AddTroon(Troon &t) {
    if (this->currentTroon.has_value()) {
        std::string message = "Link has another troon";
        std::cout << message << std::endl;
        throw std::invalid_argument(message);
    }

    this->currentTroon = t;
    this->currentTroon->setLocation(LINK);
}

