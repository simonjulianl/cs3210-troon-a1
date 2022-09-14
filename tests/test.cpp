#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/Train/Troon.h"
#include "../src/WaitingArea/WaitingArea.h"

TEST_CASE("Troon test") {
    SECTION("Instantiating troon") {
        auto first_troon = Troon(1);
        REQUIRE(first_troon.id == 1);
    }

    SECTION("Comparing Troon") {
        Troon t1{1}, t2{2};
        bool isT1LtT2 = t1 < t2;
        REQUIRE(isT1LtT2);
    }
}

TEST_CASE("Waiting Area test") {
    WaitingArea wa{};

    SECTION("Adding Troon and Remove Troon") {
        Troon t1{1};
        wa.AddTroon(t1);
        Troon top = wa.GetFrontTroon();
        REQUIRE(top == t1);
        REQUIRE(wa.IsEmpty());
    }

    SECTION("Adding Troon In Correct Order") {
        Troon t1{1}, t2{2};
        wa.AddTroon(t2);
        wa.AddTroon(t1);
        Troon top = wa.GetFrontTroon();
        REQUIRE(top == t1);
    }
}