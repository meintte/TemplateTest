#include <TemplateTest/Distributions/Dirac.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.

TEST_CASE("Dirac distribution pdf", "[Distribution][Dirac]") {
    Distribution::Dirac dirac{1.0, 0.099};
    REQUIRE(dirac.pdf(0.9) == 0.0);
    REQUIRE(dirac.pdf(0.91) == 1.0);
    REQUIRE(dirac.pdf(1.0) == 1.0);
    REQUIRE(dirac.pdf(1.09) == 1.0);
    REQUIRE(dirac.pdf(1.1) == 0.0);
}

TEST_CASE("Dirac distribution cdf", "[Distribution][Dirac]") {
    Distribution::Dirac dirac{1.0, 0.1};
    REQUIRE(dirac.cdf(0.9) == 0.0);
    REQUIRE(dirac.cdf(1.0) == 0.5);
    REQUIRE(dirac.cdf(1.1) == 1.0);
}

TEST_CASE("Dirac distribution sample", "[Distribution][Dirac]") {
    Distribution::Dirac dirac{1.0, 0.1};
    // TODO: Chi2 test
    REQUIRE(dirac.sample() == 1.0);
}

TEST_CASE("Dirac distribution min, max, mean, var, stdev",
          "[Distribution][Dirac]") {
    Distribution::Dirac dirac{1.0, 0.1};
    REQUIRE(dirac.min() == 1.0);
    REQUIRE(dirac.max() == 1.0);
    REQUIRE(dirac.mean() == 1.0);
    REQUIRE(dirac.var() == 0.0);
    REQUIRE(dirac.stdev() == 0.0);
}
// NOLINTEND (readability-function-cognitive-complexity)
