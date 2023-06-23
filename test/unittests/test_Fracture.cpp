#include <Eigen/Dense>
#include <TemplateTest/Fractures/Fracture.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

// For floating point comparisons, we need to specify a tolerance.
constexpr double relativeTolerance = 0.001;
constexpr double absoluteTolerance = 0.000001;

class MockFracture : public Fractures::Fracture {
public:
    using Fractures::Fracture::Fracture;

    double getAperture([[maybe_unused]] const Eigen::Vector2d& point) const override {
        return 1.0;
    }

    double getPermeability(
        [[maybe_unused]] const Eigen::Vector2d& point) const override {
        return 1.0;
    }

    bool fineInsideCheckFromGlobalPoint(
        [[maybe_unused]] const Eigen::Vector2d& point) const override {
        return true;
    }

    bool fineInsideCheckFromLocalPoint(
        [[maybe_unused]] const Eigen::Vector2d& point) const override {
        return true;
    }
};

TEST_CASE("Mock Fracture", "[Fractures][Fracture]") {
    SECTION("Constructor: from center and angle") {
        const Eigen::Vector2d center(1.2, 0.3);
        const double angle = 0.5;
        MockFracture fracture(center, angle);

        // SECTION("Center & angle")
        REQUIRE_THAT(
            fracture.getCenter().x(),
            Catch::Matchers::WithinAbs(center.x(), absoluteTolerance) ||
                Catch::Matchers::WithinRel(center.x(), relativeTolerance));
        REQUIRE_THAT(
            fracture.getCenter().y(),
            Catch::Matchers::WithinAbs(center.y(), absoluteTolerance) ||
                Catch::Matchers::WithinRel(center.y(), relativeTolerance));
        REQUIRE_THAT(fracture.getAngle(),
                     Catch::Matchers::WithinAbs(angle, absoluteTolerance) ||
                         Catch::Matchers::WithinRel(angle, relativeTolerance));

        // SECTION("Aperture")
        REQUIRE(fracture.getAperture(Eigen::Vector2d{0.0, 0.0}) == 1.0);

        // SECTION("Permeability")
        REQUIRE(fracture.getPermeability(Eigen::Vector2d{0.0, 0.0}) == 1.0);

        // SECTION("Family ID")
        REQUIRE(fracture.getFamilyIdName() == "Unknown");
        fracture.setFamilyIdName("Test");
        REQUIRE(fracture.getFamilyIdName() == "Test");

        // SECTION("AABB")
        REQUIRE(fracture.getAABB().min() == fracture.getAABB().max());
        REQUIRE(fracture.getAABB().min() == center);

        // SECTION("Contains")
        REQUIRE(fracture.contains(center));
        REQUIRE_FALSE(fracture.contains(center + Eigen::Vector2d{0.1, 1.1}));

        // SECTION("Transformations")
        // TODO: check how to test this (are protected/private methods)
        // REQUIRE(fracture.toLocalFrame(center) == Eigen::Vector2d{0.0, 0.0});
        // REQUIRE(fracture.toGlobalFrame(Eigen::Vector2d{0.0, 0.0}) ==
        //         center);

        // SECTION("Intersections")
        REQUIRE(fracture.fineInsideCheckFromGlobalPoint(
            center + Eigen::Vector2d{0.1, 1.1}));
        REQUIRE(
            fracture.fineInsideCheckFromLocalPoint(Eigen::Vector2d{0.1, 1.1}));
    }

    SECTION("Constructor: from start and end points") {
        const Eigen::Vector2d start(1.2, 0.3);
        const Eigen::Vector2d end(2.3, 1.4);
        MockFracture fracture(start, end);
        // Check against the other constructor as that one is tested above
        MockFracture fractureOther(Eigen::Vector2d{1.75, 0.85},
                                   0.25 * std::numbers::pi);

        REQUIRE_THAT(fracture.getCenter().x(),
                     Catch::Matchers::WithinAbs(fractureOther.getCenter().x(),
                                                absoluteTolerance) ||
                         Catch::Matchers::WithinRel(
                             fractureOther.getCenter().x(), relativeTolerance));
        REQUIRE_THAT(fracture.getCenter().y(),
                     Catch::Matchers::WithinAbs(fractureOther.getCenter().y(),
                                                absoluteTolerance) ||
                         Catch::Matchers::WithinRel(
                             fractureOther.getCenter().y(), relativeTolerance));
        REQUIRE_THAT(fracture.getAngle(),
                     Catch::Matchers::WithinAbs(fractureOther.getAngle(),
                                                absoluteTolerance) ||
                         Catch::Matchers::WithinRel(fractureOther.getAngle(),
                                                    relativeTolerance));
    }
}

// NOLINTEND (readability-function-cognitive-complexity)
