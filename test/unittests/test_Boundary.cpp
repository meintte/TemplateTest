#include <TemplateTest/Grid/Boundary.hpp>
#include <catch2/catch_test_macros.hpp>
// NOLINTBEGIN (readability-function-cognitive-complexity)

using namespace Boundary;

TEST_CASE("Type map is correct", "[Grid][Boundary]") {
    REQUIRE(type_map.size() == 4);
    REQUIRE(type_map.at("UNKNOWN") == Type::UNKNOWN);
    REQUIRE(type_map.at("DIRICHLET") == Type::DIRICHLET);
    REQUIRE(type_map.at("PERIODIC") == Type::PERIODIC);
    REQUIRE(type_map.at("NEUMANN") == Type::NEUMANN);
}

TEST_CASE("Reverse type map is correct", "[Grid][Boundary]") {
    REQUIRE(reverse_type_map.size() == 4);
    REQUIRE(reverse_type_map.at(Type::UNKNOWN) == "UNKNOWN");
    REQUIRE(reverse_type_map.at(Type::DIRICHLET) == "DIRICHLET");
    REQUIRE(reverse_type_map.at(Type::PERIODIC) == "PERIODIC");
    REQUIRE(reverse_type_map.at(Type::NEUMANN) == "NEUMANN");
}

TEST_CASE("Create boundary condition with derived type", "[Grid][Boundary]") {
    SECTION("Dirichlet") {
        auto bc = create_boundary_condition<Dirichlet>(3, 1.0);
        REQUIRE(bc.size() == 3);
        for (const auto& c : bc) {
            REQUIRE(c->type() == Type::DIRICHLET);
            REQUIRE(c->value() == 1.0);
        }
    }

    SECTION("Neumann") {
        auto bc = create_boundary_condition<Neumann>(3, 1.0);
        REQUIRE(bc.size() == 3);
        for (const auto& c : bc) {
            REQUIRE(c->type() == Type::NEUMANN);
            REQUIRE(c->value() == 1.0);
        }
    }

    SECTION("Periodic") {
        auto bc = create_boundary_condition<Periodic>(3, 1.0);
        REQUIRE(bc.size() == 3);
        for (const auto& c : bc) {
            REQUIRE(c->type() == Type::PERIODIC);
            REQUIRE(c->value() == 1.0);
        }
    }
}

TEST_CASE("Create boundary condition with type enum", "[Grid][Boundary]") {
    SECTION("Dirichlet") {
        auto bc = create_boundary_condition(3, Type::DIRICHLET, 1.0);
        REQUIRE(bc.size() == 3);
        for (const auto& c : bc) {
            REQUIRE(c->type() == Type::DIRICHLET);
            REQUIRE(c->value() == 1.0);
        }
    }

    SECTION("Neumann") {
        auto bc = create_boundary_condition(3, Type::NEUMANN, 1.0);
        REQUIRE(bc.size() == 3);
        for (const auto& c : bc) {
            REQUIRE(c->type() == Type::NEUMANN);
            REQUIRE(c->value() == 1.0);
        }
    }

    SECTION("Periodic") {
        auto bc = create_boundary_condition(3, Type::PERIODIC, 1.0);
        REQUIRE(bc.size() == 3);
        for (const auto& c : bc) {
            REQUIRE(c->type() == Type::PERIODIC);
            REQUIRE(c->value() == 1.0);
        }
    }
}

// NOLINTEND (readability-function-cognitive-complexity)
