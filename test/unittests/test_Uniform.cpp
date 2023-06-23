#include <TemplateTest/Distributions/Uniform.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.
constexpr double relativeTolerance = 0.001;
constexpr double absoluteTolerance = 0.000001;
constexpr int32_t numSamples = 10'000;

TEST_CASE("Uniform distribution pdf", "[Distribution][Uniform]") {
    Distribution::Uniform uniform{0.0, 1.0};
    REQUIRE(uniform.pdf(-0.1) == 0.0);
    REQUIRE(uniform.pdf(0.0) == 1.0);
    REQUIRE(uniform.pdf(0.5) == 1.0);
    REQUIRE(uniform.pdf(1.0) == 1.0);
    REQUIRE(uniform.pdf(1.1) == 0.0);
}

TEST_CASE("Uniform distribution cdf", "[Distribution][Uniform]") {
    Distribution::Uniform uniform{0.0, 1.0};
    REQUIRE(uniform.cdf(-0.1) == 0.0);
    REQUIRE(uniform.cdf(0.0) == 0.0);
    REQUIRE(uniform.cdf(0.25) == 0.25);
    REQUIRE(uniform.cdf(0.5) == 0.5);
    REQUIRE(uniform.cdf(0.75) == 0.75);
    REQUIRE(uniform.cdf(1.0) == 1.0);
    REQUIRE(uniform.cdf(1.1) == 1.0);
}

TEST_CASE("Uniform distribution sample", "[Distribution][Uniform]") {
    Distribution::Uniform uniform{0.0, 1.0};
    // TODO: Chi2 test
    for (int i = 0; i < numSamples; ++i) {
        double sample = uniform.sample();
        REQUIRE(sample >= 0.0);
        REQUIRE(sample <= 1.0);
    }
}

TEST_CASE("Uniform distribution min, max, mean, var, stdev",
          "[Distribution][Uniform]") {
    Distribution::Uniform uniform{0.0, 1.0};
    REQUIRE(uniform.min() == 0.0);
    REQUIRE(uniform.max() == 1.0);
    REQUIRE(uniform.mean() == 0.5);
    REQUIRE_THAT(uniform.var(),
                 Catch::Matchers::WithinAbs(1.0 / 12.0, absoluteTolerance) ||
                     Catch::Matchers::WithinRel(1.0 / 12.0, relativeTolerance));
    REQUIRE_THAT(
        uniform.stdev(),
        Catch::Matchers::WithinAbs(std::sqrt(1.0 / 12.0), absoluteTolerance) ||
            Catch::Matchers::WithinRel(std::sqrt(1.0 / 12.0),
                                       relativeTolerance));
}
// NOLINTEND (readability-function-cognitive-complexity)
