#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <TemplateTest/Random/Sampler2d.hpp>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
// NOLINTBEGIN (readability-function-cognitive-complexity)

constexpr uint32_t numSamples = 10'000;
constexpr double absoluteTolerance = 0.05;

TEST_CASE("UniformSampler2d returns a sample within the box") {
    Eigen::AlignedBox2d box(Eigen::Vector2d(-1, -1), Eigen::Vector2d(1, 1));
    Random::seed(Catch::getSeed());
    UniformSampler2d sampler(box);

    for (uint32_t i = 0; i < numSamples; ++i) {
        Eigen::Vector2d sample = sampler.sample();
        REQUIRE(box.contains(sample));
    }
}

TEST_CASE("UniformSampler2d samples uniformly within the box") {
    Eigen::AlignedBox2d box(Eigen::Vector2d(-1, -1), Eigen::Vector2d(2, 1));
    Random::seed(Catch::getSeed());
    UniformSampler2d sampler(box);

    Eigen::Vector2d sum_samples = Eigen::Vector2d::Zero();
    for (uint32_t i = 0; i < numSamples; ++i) {
        sum_samples += sampler.sample();
    }
    Eigen::Vector2d mean_sample = sum_samples / numSamples;
    REQUIRE_THAT(mean_sample.x(),
                 Catch::Matchers::WithinAbs(0.5, absoluteTolerance));
    REQUIRE_THAT(mean_sample.y(),
                 Catch::Matchers::WithinAbs(0.0, absoluteTolerance));
}
// NOLINTEND (readability-function-cognitive-complexity)
