
#include <Eigen/Dense>
#include <TemplateTest/Fractures/Fracture.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.
constexpr double relativeTolerance = 0.001;
constexpr double absoluteTolerance = 0.000001;

// Fracture parameters
Eigen::Vector2d start{-1.2, 0.3};
Eigen::Vector2d end{0.4, -2.0};
double maxAperture = 5.1;
double length = (end - start).norm();
Eigen::Vector2d center = 0.5 * (start + end);
Eigen::Vector2d mainDirection = (end - start).normalized() * length;
Eigen::Vector2d normalDirection =
    Eigen::Vector2d{-mainDirection.y(), mainDirection.x()}.normalized() *
    maxAperture;

// distance to the boundary (of the fracture) starting from which the result is
// guaranteed to be correct, smaller distance may still work, but may be invalid
// due to numerical errors
constexpr double tolerance = 1e-5;

TEST_CASE("ConstantAperture", "[Fractures][Fracture]") {
    Fractures::ConstantAperture fracture(start, end, maxAperture);

    SECTION("Check y boundary") {
        auto dx = GENERATE(-0.5 + tolerance, -0.1, 0.0, 0.3, 0.5 - tolerance);
        double dy = 0.5;
        double af = maxAperture * 2.0 * dy;
        double kf = af * af / 12.0;

        Eigen::Vector2d pos = center + dx * mainDirection;
        SECTION("Aperture") {
            // top
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
        SECTION("Permeability") {
            // top
            REQUIRE_THAT(fracture.getPermeability(pos + (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos +
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(fracture.getPermeability(pos - (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos -
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
    }
    SECTION("Check x boundary") {
        REQUIRE_THAT(fracture.getAperture(start - tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(
            fracture.getPermeability(start - tolerance * mainDirection),
            Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
    }
}

TEST_CASE("LinearAperture", "[Fractures][Fracture]") {
    Fractures::LinearAperture fracture(start, end, maxAperture);

    SECTION("Check y boundary") {
        auto dx = GENERATE(-0.5 + tolerance, -0.1, 0.0, 0.3, 0.5 - tolerance);
        double dy = 0.5 * (1.0 - 2.0 * std::abs(dx));
        double af = maxAperture * 2.0 * dy;
        double kf = af * af / 12.0;

        Eigen::Vector2d pos = center + dx * mainDirection;
        SECTION("Aperture") {
            // top
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
        SECTION("Permeability") {
            // top
            REQUIRE_THAT(fracture.getPermeability(pos + (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos +
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(fracture.getPermeability(pos - (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos -
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
    }
    SECTION("Check x boundary") {
        REQUIRE_THAT(fracture.getAperture(start - tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(
            fracture.getPermeability(start - tolerance * mainDirection),
            Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
    }
}

TEST_CASE("QuadraticAperture", "[Fractures][Fracture]") {
    Fractures::QuadraticAperture fracture(start, end, maxAperture);

    SECTION("Check y boundary") {
        auto dx = GENERATE(-0.5 + tolerance, -0.1, 0.0, 0.3, 0.5 - tolerance);
        double dy = 0.5 * (1.0 - 4.0 * dx * dx);
        double af = maxAperture * 2.0 * dy;
        double kf = af * af / 12.0;

        Eigen::Vector2d pos = center + dx * mainDirection;
        SECTION("Aperture") {
            // top
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
        SECTION("Permeability") {
            // top
            REQUIRE_THAT(fracture.getPermeability(pos + (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos +
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(fracture.getPermeability(pos - (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos -
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
    }
    SECTION("Check x boundary") {
        REQUIRE_THAT(fracture.getAperture(start - tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(
            fracture.getPermeability(start - tolerance * mainDirection),
            Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
    }
}

TEST_CASE("EllipticAperture", "[Fractures][Fracture]") {
    Fractures::EllipticAperture fracture(start, end, maxAperture);

    SECTION("Check y boundary") {
        auto dx = GENERATE(-0.5 + tolerance, -0.1, 0.0, 0.3, 0.5 - tolerance);
        double dy = 0.5 * std::sqrt(1.0 - 4.0 * dx * dx);
        double af = maxAperture * 2.0 * dy;
        double kf = af * af / 12.0;

        Eigen::Vector2d pos = center + dx * mainDirection;
        SECTION("Aperture") {
            // top
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
        SECTION("Permeability") {
            // top
            REQUIRE_THAT(fracture.getPermeability(pos + (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos +
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(fracture.getPermeability(pos - (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos -
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
    }
    SECTION("Check x boundary") {
        REQUIRE_THAT(fracture.getAperture(start - tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(
            fracture.getPermeability(start - tolerance * mainDirection),
            Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
    }
}

TEST_CASE("OneSidedLinearAperture", "[Fractures][Fracture]") {
    Fractures::OneSidedLinearAperture fracture(start, end, maxAperture);

    SECTION("Check y boundary") {
        auto dx = GENERATE(-0.5 + tolerance, -0.1, 0.0, 0.3, 0.5 - tolerance);
        double dy = 0.5 * (dx + 0.5);
        double af = maxAperture * 2.0 * dy;
        double kf = af * af / 12.0;

        Eigen::Vector2d pos = center + dx * mainDirection;
        SECTION("Aperture") {
            // top
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos + (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy - tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(af, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(af, relativeTolerance));
            REQUIRE_THAT(
                fracture.getAperture(pos - (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
        SECTION("Permeability") {
            // top
            REQUIRE_THAT(fracture.getPermeability(pos + (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos +
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
            // bottom
            REQUIRE_THAT(fracture.getPermeability(pos - (dy - tolerance) *
                                                            normalDirection),
                         Catch::Matchers::WithinAbs(kf, absoluteTolerance) ||
                             Catch::Matchers::WithinRel(kf, relativeTolerance));
            REQUIRE_THAT(
                fracture.getPermeability(pos -
                                         (dy + tolerance) * normalDirection),
                Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                    Catch::Matchers::WithinRel(0.0, relativeTolerance));
        }
    }
    SECTION("Check x boundary") {
        REQUIRE_THAT(fracture.getAperture(start - tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(
            fracture.getPermeability(start - tolerance * mainDirection),
            Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                Catch::Matchers::WithinRel(0.0, relativeTolerance));
        REQUIRE_THAT(fracture.getAperture(end + tolerance * mainDirection),
                     Catch::Matchers::WithinAbs(0.0, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(0.0, relativeTolerance));
    }
}

// NOLINTEND (readability-function-cognitive-complexity)
