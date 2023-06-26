#include <TemplateTest/Fractures/Fracture.hpp>
#include <numbers>
namespace Fractures {

Fracture::Fracture(Eigen::Vector2d center, double angle)
    : m_center(std::move(center)), m_angle(angle), m_aabb(m_center) {}

Fracture::Fracture(const Eigen::Vector2d& start, const Eigen::Vector2d& end)
    : m_center(0.5 * (start + end)),
      m_angle(std::atan2(end.y() - start.y(), end.x() - start.x())),
      m_aabb(m_center) {}

bool Fracture::contains(const Eigen::Vector2d& point) const {
    if (!m_aabb.contains(point)) {
        return false;
    }
    return fineInsideCheckFromGlobalPoint(point);
}

const Eigen::Vector2d& Fracture::getCenter() const { return m_center; }

double Fracture::getAngle() const { return m_angle; }

void Fracture::setFamilyIdName(const std::string& name) {
    m_fracFamilyIdName = name;
}

const std::string& Fracture::getFamilyIdName() const {
    return m_fracFamilyIdName;
}

const Eigen::AlignedBox2d& Fracture::getAABB() const { return m_aabb; }

Eigen::Vector2d Fracture::toLocalFrame(const Eigen::Vector2d& point) const {
    return Eigen::Rotation2Dd(-m_angle) * (point - m_center);
}

Eigen::Vector2d Fracture::toGlobalFrame(const Eigen::Vector2d& point) const {
    return Eigen::Rotation2Dd(m_angle) * point + m_center;
}

FromApertureFunction::FromApertureFunction(Eigen::Vector2d center, double angle,
                                           double length, double maxAperture)
    : Fracture(std::move(center), angle),
      m_length(length),
      m_maxAperture(maxAperture) {
    m_aabb.extend(
        toGlobalFrame(Eigen::Vector2d(-0.5 * m_length, -0.5 * m_maxAperture)));
    m_aabb.extend(
        toGlobalFrame(Eigen::Vector2d(-0.5 * m_length, 0.5 * m_maxAperture)));
    m_aabb.extend(
        toGlobalFrame(Eigen::Vector2d(0.5 * m_length, -0.5 * m_maxAperture)));
    m_aabb.extend(
        toGlobalFrame(Eigen::Vector2d(0.5 * m_length, 0.5 * m_maxAperture)));
}

FromApertureFunction::FromApertureFunction(const Eigen::Vector2d& start,
                                           const Eigen::Vector2d& end,
                                           double maxAperture)
    : FromApertureFunction(0.5 * (start + end),
                           std::atan2(end.y() - start.y(), end.x() - start.x()),
                           (end - start).norm(), maxAperture) {}

bool FromApertureFunction::fineInsideCheckFromGlobalPoint(
    const Eigen::Vector2d& point) const {
    return fineInsideCheckFromLocalPoint(toLocalFrame(point));
}
bool FromApertureFunction::fineInsideCheckFromLocalPoint(
    const Eigen::Vector2d& point) const {
    const double x = point.x();
    const double y = point.y();

    if (std::abs(x) > 0.5 * m_length) {
        return false;
    }
    return std::abs(y) <= 0.5 * apertureFunction(x);
}

double FromApertureFunction::getAperture(const Eigen::Vector2d& point) const {
    const Eigen::Vector2d localPoint = toLocalFrame(point);

    if (!fineInsideCheckFromLocalPoint(localPoint)) {
        return 0.0;
    }
    return apertureFunction(localPoint.x());
}

double FromApertureFunction::getPermeability(
    const Eigen::Vector2d& point) const {
    const double aperture = getAperture(point);
    // parallel plate flow (Hagen-Poiseuille, cubic law)
    return aperture * aperture / 12.0;
}

double ConstantAperture::getArea() const { return m_length * m_maxAperture; }
double ConstantAperture::apertureFunction(double x) const {
    if (2.0 * std::abs(x) <= m_length) {
        return m_maxAperture;
    }
    return 0.0;
}

double LinearAperture::getArea() const {
    return m_length * m_maxAperture * 0.5;
}
double LinearAperture::apertureFunction(double x) const {
    const double abs2x = 2.0 * std::abs(x);
    if (abs2x <= m_length) {
        return m_maxAperture * (1.0 - abs2x / m_length);
    }
    return 0.0;
}

double QuadraticAperture::getArea() const {
    return m_length * m_maxAperture * 4.0 / 3.0;
}
double QuadraticAperture::apertureFunction(double x) const {
    if (2.0 * std::abs(x) <= m_length) {
        return m_maxAperture * (1.0 - 4.0 * x * x / (m_length * m_length));
    }
    return 0.0;
}

double EllipticAperture::getArea() const {
    return m_length * m_maxAperture * 0.25 * std::numbers::pi;
}
double EllipticAperture::apertureFunction(double x) const {
    if (2.0 * std::abs(x) <= m_length) {
        return m_maxAperture *
               std::sqrt(1.0 - 4.0 * x * x / (m_length * m_length));
    }
    return 0.0;
}

double OneSidedLinearAperture::getArea() const {
    return m_length * m_maxAperture * 0.5;
}
double OneSidedLinearAperture::apertureFunction(double x) const {
    if (2.0 * std::abs(x) <= m_length) {
        return m_maxAperture * (x / m_length + 0.5);
    }
    return 0.0;
}

}  // namespace Fractures