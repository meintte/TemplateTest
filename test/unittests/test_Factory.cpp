#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <TemplateTest/Fractures/Factory.hpp>
#include <TemplateTest/Fractures/Fracture.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <iostream>
#include <memory>
#include <numbers>
// NOLINTBEGIN (readability-function-cognitive-complexity)
constexpr uint32_t numSamples = 1'000;

using namespace Fractures;

TEST_CASE(
    "createFracture returns a single fracture with probability proportional to "
    "number density * area",
    "[Fractures][Factory]") {
    // create a factory with two families
    auto factory = std::make_unique<Factory>();
    auto family1 = std::make_unique<ConstantFractureFamily>(
        0.1, 0.02, 0.19 * std::numbers::pi);
    auto family2 = std::make_unique<LinearFractureFamily>(
        0.1, 0.02, 0.19 * std::numbers::pi);
    Eigen::AlignedBox2d box1(Eigen::Vector2d(0.0, 0.0),
                             Eigen::Vector2d(1.0, 1.0));
    auto sampler1 = std::make_shared<UniformSampler2d>(box1);
    Eigen::AlignedBox2d box2(Eigen::Vector2d(-0.5, 0.1),
                             Eigen::Vector2d(1.0, 1.0));
    auto sampler2 = std::make_shared<UniformSampler2d>(box2);
    double numberDensity1 = 0.5;
    double numberDensity2 = 0.3;

    auto family1IdName = family1->getIdName();
    auto family2IdName = family2->getIdName();
    factory->registerFamily(std::move(family1), sampler1, numberDensity1);
    factory->registerFamily(std::move(family2), sampler2, numberDensity2);

    uint32_t numFamily1 = 0;
    uint32_t numFamily2 = 0;
    for (uint32_t i = 0; i < numSamples; ++i) {
        // create a fracture and check that it belongs to one of the families
        auto fracture = factory->createFracture();
        REQUIRE(fracture != nullptr);
        bool isFamily1 = fracture->getFamilyIdName() == family1IdName;
        bool isFamily2 = fracture->getFamilyIdName() == family2IdName;
        if (isFamily1) {
            REQUIRE_FALSE(isFamily2);
            numFamily1++;
        }
        if (isFamily2) {
            REQUIRE_FALSE(isFamily1);
            numFamily2++;
        }
    }
    REQUIRE_THAT(numFamily1 / static_cast<double>(numFamily1 + numFamily2),
                 Catch::Matchers::WithinAbs(0.5524861878453039, 0.001));
    REQUIRE_THAT(numFamily2 / static_cast<double>(numFamily1 + numFamily2),
                 Catch::Matchers::WithinAbs(0.4475138121546961, 0.001));
}

TEST_CASE("getFamilyIdNames returns the names of all registered families",
          "[Fractures][Factory]") {
    // create a factory with two families
    auto factory = std::make_unique<Factory>();
    auto family1 = std::make_unique<QuadraticFractureFamily>(
        0.1, 0.02, 0.19 * std::numbers::pi);
    auto family2 = std::make_unique<EllipticFractureFamily>(0.5, 0.03, 0);
    auto sampler = std::make_shared<UniformSampler2d>(Eigen::AlignedBox2d());
    double numberDensity1 = 0.5;
    double numberDensity2 = 0.3;
    factory->registerFamily(std::move(family1), sampler, numberDensity1);
    factory->registerFamily(std::move(family2), sampler, numberDensity2);

    // check that the names of the families are returned correctly
    std::vector<std::string> familyIdNames = factory->getFamilyIdNames();
    REQUIRE(familyIdNames.size() == 2);
    REQUIRE(familyIdNames[0] == "QuadraticFractureFamily0.10.020.596903");
    REQUIRE(familyIdNames[1] == "EllipticFractureFamily0.50.030");
}

// NOLINTEND (readability-function-cognitive-complexity)
