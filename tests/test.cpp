#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/Train/Troon.h"
#include "../src/WaitingArea/WaitingArea.h"

TEST_CASE("Troon test") {
    SECTION("Instantiating troon") {
        auto first_troon = Troon(1, y, "source", "destination", PLATFORM);
        REQUIRE(first_troon.id == 1);
    }

    SECTION("Comparing Troon") {
        Troon t1{1, y, "source", "destination", PLATFORM};
        Troon t2{2, y, "source", "destination", PLATFORM};
        bool isT1LtT2 = t1 < t2;
        REQUIRE(isT1LtT2);
    }

    SECTION("Printing Troon") {
        Troon t1{1, y, "source", "destination", LINK};
        string expected = "y1-source->destination";
        REQUIRE(t1.GenerateDescription() == expected);
    }
}

TEST_CASE("Waiting Area test") {
    WaitingArea wa{};

    SECTION("Adding Troon and Remove Troon") {
        Troon t1{1, y, "source", "destination", PLATFORM};
        wa.AddTroon(t1);
        Troon top = wa.GetFrontTroon();
        REQUIRE(top == t1);
        REQUIRE(wa.IsEmpty());
    }

    SECTION("Adding Troon In Correct Order") {
        Troon t1{1, y, "source", "destination", PLATFORM};
        Troon t2{2, y, "source", "destination", PLATFORM};
        wa.AddTroon(t2);
        wa.AddTroon(t1);
        Troon top = wa.GetFrontTroon();
        REQUIRE(top == t1);
    }
}