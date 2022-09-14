#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Sample testing code
static int Factorial(int number) {
    return number <= 1 ? 1 : Factorial(number - 1) * number;  // pass
}

TEST_CASE("Factorial of 0 is 1 (fail)", "[single-file]") {
    REQUIRE(Factorial(0) == 1);
}

TEST_CASE("Factorials of 1 and higher are computed (pass)", "[single-file]") {
    REQUIRE(Factorial(1) == 1);
}