#include <TemplateTest/Grid/Domain.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.
constexpr double relativeTolerance = 0.001;
constexpr double absoluteTolerance = 0.000001;

// NOLINTEND (readability-function-cognitive-complexity)
