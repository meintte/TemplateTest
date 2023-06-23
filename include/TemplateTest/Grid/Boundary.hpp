#pragma once
#include <concepts>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Boundary {
enum class Type { UNKNOWN, DIRICHLET, NEUMANN, PERIODIC };

static inline const std::map<std::string, Type> type_map = {
    {"UNKNOWN", Type::UNKNOWN},
    {"DIRICHLET", Type::DIRICHLET},
    {"PERIODIC", Type::PERIODIC},
    {"NEUMANN", Type::NEUMANN}};

static inline const std::map<Type, std::string> reverse_type_map = [] {
    std::map<Type, std::string> m;
    for (const auto& [k, v] : type_map) {
        m.emplace_hint(m.end(), v, k);
    }
    return m;
}();

class Condition {
public:
    [[nodiscard]] Type type() const { return m_type; }
    [[nodiscard]] double value() const { return m_value; }

protected:
    explicit Condition(Type type = Type::UNKNOWN, double value = 0.0)
        : m_type(type), m_value(value) {}

    Type m_type;
    double m_value;
};

class Dirichlet : public Condition {
public:
    explicit Dirichlet(double value = 0.0)
        : Condition(Type::DIRICHLET, value) {}
};

class Neumann : public Condition {
public:
    explicit Neumann(double value = 0.0) : Condition(Type::NEUMANN, value) {}
};

class Periodic : public Condition {
public:
    // pressure drop is messured from west to east or from south to north
    explicit Periodic(double dp = 0.0) : Condition(Type::PERIODIC, dp) {}
};

template <typename BoundaryConditionType, typename... Args>
    requires std::derived_from<BoundaryConditionType, Condition>
std::vector<std::unique_ptr<Condition>> create_boundary_condition(
    int n, Args&&... args) {
    std::vector<std::unique_ptr<Condition>> bc;
    bc.reserve(static_cast<std::size_t>(n));
    for (int32_t i = 0; i < n; ++i) {
        bc.emplace_back(std::make_unique<BoundaryConditionType>(
            std::forward<Args>(args)...));
    }
    return bc;
}

template <typename... Args>
std::vector<std::unique_ptr<Condition>> create_boundary_condition(
    int n, Type btype, Args&&... args) {
    switch (btype) {
        case Type::DIRICHLET:
            return create_boundary_condition<Dirichlet>(
                n, std::forward<Args>(args)...);
        case Type::NEUMANN:
            return create_boundary_condition<Neumann>(
                n, std::forward<Args>(args)...);
        case Type::PERIODIC:
            return create_boundary_condition<Periodic>(
                n, std::forward<Args>(args)...);
        default:
            throw std::runtime_error("Unknown boundary condition type");
    }
}
}  // namespace Boundary
