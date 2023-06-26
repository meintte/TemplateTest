#include <TemplateTest/Distributions/MultiDirac.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.

TEST_CASE("Multi Dirac input validation", "[Distributions][MultiDirac]") {
    REQUIRE_THROWS_AS(Distribution::MultiDirac({1.0}, {1.0, 1.0}),
                      std::invalid_argument);
    REQUIRE_THROWS_AS(Distribution::MultiDirac({}, {}), std::invalid_argument);
}

TEST_CASE("MultiDirac distribution pdf", "[Distribution][MultiDirac]") {
    std::vector<double> x = {1.0, 2.0, 3.0};
    std::vector<double> weights = {0.2, 0.5, 0.3};
    constexpr double tol = 0.1;
    Distribution::MultiDirac mdirac{x, weights, tol};
    REQUIRE(mdirac.pdf(1.0) == 0.2);
    REQUIRE(mdirac.pdf(2.0) == 0.5);
    REQUIRE(mdirac.pdf(3.0) == 0.3);
    REQUIRE(mdirac.pdf(0.0) == 0.0);
    REQUIRE(mdirac.pdf(5.0) == 0.0);
}

TEST_CASE("Dirac distribution cdf", "[Distribution][MultiDirac]") {
    std::vector<double> x = {1.0, 2.0, 3.0};
    std::vector<double> weights = {0.2, 0.5, 0.3};
    constexpr double tol = 0.01;
    Distribution::MultiDirac mdirac{x, weights, tol};
    REQUIRE(mdirac.cdf(1.0) == 0.2);
    REQUIRE(mdirac.cdf(2.0) == 0.7);
    REQUIRE(mdirac.cdf(3.0) == 1.0);
    REQUIRE(mdirac.cdf(0.0) == 0.0);
    REQUIRE(mdirac.cdf(5.0) == 1.0);
}

TEST_CASE("Dirac distribution sample", "[Distribution][MultiDirac]") {
    std::vector<double> x = {1.0, 2.0, 3.0};
    std::vector<double> weights = {0.2, 0.5, 0.3};
    Distribution::MultiDirac mdirac{x, weights};
    // TODO: Chi2 test
    REQUIRE(mdirac.sample() >= 1.0);
}

TEST_CASE("Dirac distribution min, max, mean, var, stdev",
          "[Distribution][MultiDirac]") {
    std::vector<double> x = {1.0, 2.0, 3.0};
    std::vector<double> weights = {0.2, 0.5, 0.3};
    Distribution::MultiDirac mdirac{x, weights};
    REQUIRE(mdirac.min() == 1.0);
    REQUIRE(mdirac.max() == 3.0);
    REQUIRE_THAT(mdirac.mean(), Catch::Matchers::WithinAbs(2.1, 1e-7));
    REQUIRE_THAT(mdirac.var(), Catch::Matchers::WithinAbs(0.49, 1e-7));
    REQUIRE_THAT(mdirac.stdev(), Catch::Matchers::WithinAbs(0.7, 1e-7));
}

// NOLINTEND (readability-function-cognitive-complexity)
