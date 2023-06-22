#include <TemplateTest/Grid/Domain.hpp>
#include <catch2/catch_test_macros.hpp>
// #include <catch2/catch_approx.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.
constexpr double relativeTolerance = 0.001;
constexpr double absoluteTolerance = 0.000001;
// TODO: catch2 constexpr matchers for floating point comparisons?
constexpr bool checkEqual(double test, double expected) {
    return std::abs(test - expected) < absoluteTolerance ||
           std::abs(test - expected) < relativeTolerance * std::abs(expected);
}

TEST_CASE("Domain class tests", "[Domain]") {
    constexpr Domain domain{10, 20, 1.0, 2.0};
    SECTION("Constructor") {
        STATIC_REQUIRE(domain.nx == 10);
        STATIC_REQUIRE(domain.ny == 20);
        STATIC_REQUIRE(domain.Lx == 1.0);
        STATIC_REQUIRE(domain.Ly == 2.0);
        STATIC_REQUIRE(domain.hx == 0.1);
        STATIC_REQUIRE(domain.hy == 0.1);
    }

    SECTION("x and y functions") {
        STATIC_REQUIRE(checkEqual(domain.x(0), 0.05));
        STATIC_REQUIRE(checkEqual(domain.y(0), 0.05));
        STATIC_REQUIRE(checkEqual(domain.x(9), 0.95));
        STATIC_REQUIRE(checkEqual(domain.y(19), 1.95));
    }

    SECTION("i and j functions") {
        STATIC_REQUIRE(domain.i(0.05) == 0);
        STATIC_REQUIRE(domain.j(0.05) == 0);
        STATIC_REQUIRE(domain.i(0.95) == 9);
        STATIC_REQUIRE(domain.j(1.95) == 19);
    }
}
// NOLINTEND (readability-function-cognitive-complexity)
