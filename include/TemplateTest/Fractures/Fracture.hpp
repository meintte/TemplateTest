#pragma once
#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace Fractures {

class Fracture {
public:
    Fracture(Eigen::Vector2d center, double angle);
    Fracture(const Eigen::Vector2d& start, const Eigen::Vector2d& end);
    virtual ~Fracture() = default;

    [[nodiscard]] bool contains(const Eigen::Vector2d& point) const;

    const Eigen::Vector2d& getCenter() const;
    double getAngle() const;
    virtual double getArea() const = 0;

    virtual double getAperture(const Eigen::Vector2d& point) const = 0;
    virtual double getPermeability(const Eigen::Vector2d& point) const = 0;

    void setFamilyIdName(const std::string& name);
    const std::string& getFamilyIdName() const;

    const Eigen::AlignedBox2d& getAABB() const;

protected:
    Eigen::Vector2d toLocalFrame(const Eigen::Vector2d& point) const;

    Eigen::Vector2d toGlobalFrame(const Eigen::Vector2d& point) const;

    virtual bool fineInsideCheckFromGlobalPoint(
        const Eigen::Vector2d& point) const = 0;
    virtual bool fineInsideCheckFromLocalPoint(
        const Eigen::Vector2d& point) const = 0;

    Eigen::Vector2d m_center;
    double m_angle;

    Eigen::AlignedBox2d m_aabb;

    std::string m_fracFamilyIdName = "Unknown";
};

class FromApertureFunction : public Fracture {
public:
    FromApertureFunction(Eigen::Vector2d center, double angle, double length,
                         double maxAperture);
    FromApertureFunction(const Eigen::Vector2d& start,
                         const Eigen::Vector2d& end, double maxAperture);

    double getAperture(const Eigen::Vector2d& point) const override;
    double getPermeability(const Eigen::Vector2d& point) const override;

protected:
    virtual double apertureFunction(double x) const = 0;

    bool fineInsideCheckFromGlobalPoint(
        const Eigen::Vector2d& point) const override;
    bool fineInsideCheckFromLocalPoint(
        const Eigen::Vector2d& point) const override;

    double m_length;
    double m_maxAperture;
};

class ConstantAperture final : public FromApertureFunction {
public:
    using FromApertureFunction::FromApertureFunction;

    double getArea() const override;

protected:
    double apertureFunction(double x) const override;
};

class LinearAperture final : public FromApertureFunction {
public:
    using FromApertureFunction::FromApertureFunction;

    double getArea() const override;

protected:
    double apertureFunction(double x) const override;
};

class QuadraticAperture final : public FromApertureFunction {
public:
    using FromApertureFunction::FromApertureFunction;

    double getArea() const override;

protected:
    double apertureFunction(double x) const override;
};

class EllipticAperture final : public FromApertureFunction {
public:
    using FromApertureFunction::FromApertureFunction;

    double getArea() const override;

protected:
    double apertureFunction(double x) const override;
};

class OneSidedLinearAperture final : public FromApertureFunction {
public:
    using FromApertureFunction::FromApertureFunction;

    double getArea() const override;

protected:
    double apertureFunction(double x) const override;
};

}  // namespace Fractures
