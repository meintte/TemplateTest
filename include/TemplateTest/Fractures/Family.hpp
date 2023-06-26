#pragma once
#include <TemplateTest/Fractures/Fracture.hpp>
#include <memory>

namespace Fractures {
class Family {
public:
    virtual ~Family() = default;

    virtual std::unique_ptr<Fracture> createFracture(
        const Eigen::Vector2d& pos) const = 0;

    virtual const std::string& getIdName() const = 0;

protected:
    template <typename... Args>
    static std::string createIdName(Args&&... args) {
        // concatenates all arguments which should be an unique identifier
        std::stringstream idName;
        ((idName << args), ...);
        return idName.str();
    }
};

class TempNameFamily : public Family {
public:
    const std::string& getIdName() const override { return m_idName; }

protected:
    TempNameFamily(std::string_view className, double lf, double af,
                   double angle = 0.0);
    double m_lf;
    double m_af;
    double m_angle;
    std::string m_idName;
};

class ConstantFractureFamily : public TempNameFamily {
public:
    ConstantFractureFamily(double lf, double af, double angle = 0.0);

    std::unique_ptr<Fracture> createFracture(
        const Eigen::Vector2d& pos) const override;
};

class LinearFractureFamily : public TempNameFamily {
public:
    LinearFractureFamily(double lf, double af, double angle = 0.0);

    std::unique_ptr<Fracture> createFracture(
        const Eigen::Vector2d& pos) const override;
};

class QuadraticFractureFamily : public TempNameFamily {
public:
    QuadraticFractureFamily(double lf, double af, double angle = 0.0);

    std::unique_ptr<Fracture> createFracture(
        const Eigen::Vector2d& pos) const override;
};

class EllipticFractureFamily : public TempNameFamily {
public:
    EllipticFractureFamily(double lf, double af, double angle = 0.0);

    std::unique_ptr<Fracture> createFracture(
        const Eigen::Vector2d& pos) const override;
};

class OneSidedLinearFractureFamily : public TempNameFamily {
public:
    OneSidedLinearFractureFamily(double lf, double af, double angle = 0.0);

    std::unique_ptr<Fracture> createFracture(
        const Eigen::Vector2d& pos) const override;
};

}  // namespace Fractures
