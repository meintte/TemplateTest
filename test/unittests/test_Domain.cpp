#include <TemplateTest/Grid/Domain.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.
constexpr double relativeTolerance = 0.001;
constexpr double absoluteTolerance = 0.000001;

TEST_CASE("Domain class tests", "[Domain]") {
    constexpr Domain domain{10, 20, 1.0, 2.0};
    SECTION("Constructor") {
        REQUIRE(domain.nx == 10);
        REQUIRE(domain.ny == 20);
        REQUIRE(domain.Lx == 1.0);
        REQUIRE(domain.Ly == 2.0);
        REQUIRE(domain.hx == 0.1);
        REQUIRE(domain.hy == 0.1);
    }

    SECTION("x and y functions") {
        REQUIRE_THAT(domain.x(0),
                     Catch::Matchers::WithinAbs(0.05, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.05, relativeTolerance));
        REQUIRE_THAT(domain.y(0),
                     Catch::Matchers::WithinAbs(0.05, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.05, relativeTolerance));
        REQUIRE_THAT(domain.x(9),
                     Catch::Matchers::WithinAbs(0.95, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.95, relativeTolerance));
        REQUIRE_THAT(domain.y(19),
                     Catch::Matchers::WithinAbs(1.95, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(1.95, relativeTolerance));
    }

    SECTION("i and j functions") {
        REQUIRE(domain.i(0.05) == 0);
        REQUIRE(domain.j(0.05) == 0);
        REQUIRE(domain.i(0.95) == 9);
        REQUIRE(domain.j(1.95) == 19);
    }
}
// NOLINTEND (readability-function-cognitive-complexity)
