#include <Eigen/Dense>
#include <TemplateTest/Fractures/Family.hpp>
#include <TemplateTest/Fractures/Fracture.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numbers>
// NOLINTBEGIN (readability-function-cognitive-complexity)

TEST_CASE("Fracture Family", "[Fractures][Family]") {
    double lf = 1.2;
    double af = 0.3;
    double angle = 0.21 * std::numbers::pi;
    std::string idParameterPart = "1.20.30.659734";

    SECTION("Constant Aperture") {
        Fractures::ConstantFractureFamily family(lf, af, angle);
        REQUIRE(dynamic_cast<Fractures::ConstantAperture*>(
                    family.createFracture(Eigen::Vector2d{0.0, 0.0}).get()) !=
                nullptr);
        REQUIRE(family.getIdName() ==
                "ConstantFractureFamily" + idParameterPart);
        REQUIRE(family.createFracture(Eigen::Vector2d{0.0, 0.0}) != nullptr);
    }

    SECTION("Linear Aperture") {
        Fractures::LinearFractureFamily family(lf, af, angle);
        REQUIRE(dynamic_cast<Fractures::LinearAperture*>(
                    family.createFracture(Eigen::Vector2d{0.0, 0.0}).get()) !=
                nullptr);
        REQUIRE(family.getIdName() == "LinearFractureFamily" + idParameterPart);
        REQUIRE(family.createFracture(Eigen::Vector2d{0.0, 0.0}) != nullptr);
    }

    SECTION("Quadratic Aperture") {
        Fractures::QuadraticFractureFamily family(lf, af, angle);
        REQUIRE(dynamic_cast<Fractures::QuadraticAperture*>(
                    family.createFracture(Eigen::Vector2d{0.0, 0.0}).get()) !=
                nullptr);
        REQUIRE(family.getIdName() ==
                "QuadraticFractureFamily" + idParameterPart);
        REQUIRE(family.createFracture(Eigen::Vector2d{0.0, 0.0}) != nullptr);
    }

    SECTION("Elliptic Aperture") {
        Fractures::EllipticFractureFamily family(lf, af, angle);
        REQUIRE(dynamic_cast<Fractures::EllipticAperture*>(
                    family.createFracture(Eigen::Vector2d{0.0, 0.0}).get()) !=
                nullptr);
        REQUIRE(family.getIdName() ==
                "EllipticFractureFamily" + idParameterPart);
        REQUIRE(family.createFracture(Eigen::Vector2d{0.0, 0.0}) != nullptr);
    }

    SECTION("OneSidedLinear Aperture") {
        Fractures::OneSidedLinearFractureFamily family(lf, af, angle);
        REQUIRE(dynamic_cast<Fractures::OneSidedLinearAperture*>(
                    family.createFracture(Eigen::Vector2d{0.0, 0.0}).get()) !=
                nullptr);
        REQUIRE(family.getIdName() ==
                "OneSidedLinearFractureFamily" + idParameterPart);
        REQUIRE(family.createFracture(Eigen::Vector2d{0.0, 0.0}) != nullptr);
    }
}

// NOLINTEND (readability-function-cognitive-complexity)
