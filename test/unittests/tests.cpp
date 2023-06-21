#include <catch2/catch_test_macros.hpp>
#include <TemplateTest/sample_library.hpp>

TEST_CASE("Factorials are computed", "[sample_library][factorial]") {
    REQUIRE(factorial(0) == 1);
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}
