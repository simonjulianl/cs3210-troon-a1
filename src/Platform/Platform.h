#ifndef CS3210_A1_A1_A0196678A_A0219768L_PLATFORM_H
#define CS3210_A1_A1_A0196678A_A0219768L_PLATFORM_H

#include "../Train/Troon.h"
#include "../Link/Link.h"
#include <optional>

class Platform {
public:
    optional<Troon> currentTroon = std::nullopt;
    optional<Link> nextLink = std::nullopt;

    int popularity;
    int currentCounter = 0;

    explicit Platform(int popularity) : popularity{popularity} {};

    void ProcessPlatform();

    void AddTroon(Troon &t);
};


#endif //CS3210_A1_A1_A0196678A_A0219768L_PLATFORM_H
