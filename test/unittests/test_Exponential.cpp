#include <TemplateTest/Distributions/Exponential.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.
constexpr double relativeTolerance = 0.001;
constexpr double absoluteTolerance = 0.000001;
constexpr int32_t numSamples = 10'000;

TEST_CASE("Exponential distribution pdf", "[Distribution][Exponential]") {
    Distribution::Exponential exponential{1.0};
    REQUIRE(exponential.pdf(-0.1) == 0.0);
    REQUIRE(exponential.pdf(0.0) == 1.0);
    REQUIRE_THAT(
        exponential.pdf(1.0),
        Catch::Matchers::WithinAbs(0.36787944117, absoluteTolerance) ||
            Catch::Matchers::WithinRel(0.36787944117, relativeTolerance));
    REQUIRE_THAT(
        exponential.pdf(2.0),
        Catch::Matchers::WithinAbs(0.13533528323, absoluteTolerance) ||
            Catch::Matchers::WithinRel(0.13533528323, relativeTolerance));
}

TEST_CASE("Exponential distribution cdf", "[Distribution][Exponential]") {
    Distribution::Exponential exponential{1.0};
    REQUIRE(exponential.cdf(-0.1) == 0.0);
    REQUIRE(exponential.cdf(0.0) == 0.0);
    REQUIRE_THAT(
        exponential.cdf(1.0),
        Catch::Matchers::WithinAbs(0.63212055883, absoluteTolerance) ||
            Catch::Matchers::WithinRel(0.63212055883, relativeTolerance));
    REQUIRE_THAT(
        exponential.cdf(2.0),
        Catch::Matchers::WithinAbs(0.86466471676, absoluteTolerance) ||
            Catch::Matchers::WithinRel(0.86466471676, relativeTolerance));
}

TEST_CASE("Exponential distribution sample", "[Distribution][Exponential]") {
    Distribution::Exponential exponential{1.0};
    // TODO: Chi2 test
    for (int32_t i = 0; i < numSamples; ++i) {
        double sample = exponential.sample();
        REQUIRE(sample >= 0.0);
    }
}

TEST_CASE("Exponential distribution min, max, mean, var, stdev",
          "[Distribution][Exponential]") {
    Distribution::Exponential exponential{2.0};
    REQUIRE(exponential.min() == 0.0);
    REQUIRE(exponential.max() == std::numeric_limits<double>::infinity());
    REQUIRE(exponential.mean() == 0.5);
    REQUIRE(exponential.var() ==  0.25);
    REQUIRE(exponential.stdev() ==  0.5);
}
// NOLINTEND (readability-function-cognitive-complexity)
