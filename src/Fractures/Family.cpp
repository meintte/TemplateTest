#include <TemplateTest/Fractures/Family.hpp>

namespace Fractures {

TempNameFamily::TempNameFamily(std::string_view className, double lf, double af,
                               double angle)
    : m_lf{lf},
      m_af{af},
      m_angle{angle},
      m_idName{createIdName(className, lf, af, angle)} {}

ConstantFractureFamily::ConstantFractureFamily(double lf, double af,
                                               double angle)
    : TempNameFamily("ConstantFractureFamily", lf, af, angle) {}

std::unique_ptr<Fracture> ConstantFractureFamily::createFracture(
    const Eigen::Vector2d& pos) const {
    auto frac = std::make_unique<ConstantAperture>(pos, m_angle, m_lf, m_af);
    frac->setFamilyIdName(m_idName);
    return frac;
}

LinearFractureFamily::LinearFractureFamily(double lf, double af, double angle)
    : TempNameFamily("LinearFractureFamily", lf, af, angle) {}

std::unique_ptr<Fracture> LinearFractureFamily::createFracture(
    const Eigen::Vector2d& pos) const {
    auto frac = std::make_unique<LinearAperture>(pos, m_angle, m_lf, m_af);
    frac->setFamilyIdName(m_idName);
    return frac;
}

QuadraticFractureFamily::QuadraticFractureFamily(double lf, double af,
                                                 double angle)
    : TempNameFamily("QuadraticFractureFamily", lf, af, angle) {}

std::unique_ptr<Fracture> QuadraticFractureFamily::createFracture(
    const Eigen::Vector2d& pos) const {
    auto frac = std::make_unique<QuadraticAperture>(pos, m_angle, m_lf, m_af);
    frac->setFamilyIdName(m_idName);
    return frac;
}

EllipticFractureFamily::EllipticFractureFamily(double lf, double af,
                                               double angle)
    : TempNameFamily("EllipticFractureFamily", lf, af, angle) {}

std::unique_ptr<Fracture> EllipticFractureFamily::createFracture(
    const Eigen::Vector2d& pos) const {
    auto frac = std::make_unique<EllipticAperture>(pos, m_angle, m_lf, m_af);
    frac->setFamilyIdName(m_idName);
    return frac;
}

OneSidedLinearFractureFamily::OneSidedLinearFractureFamily(double lf, double af,

                                                           double angle)
    : TempNameFamily("OneSidedLinearFractureFamily", lf, af, angle) {}

std::unique_ptr<Fracture> OneSidedLinearFractureFamily::createFracture(
    const Eigen::Vector2d& pos) const {
    auto frac =
        std::make_unique<OneSidedLinearAperture>(pos, m_angle, m_lf, m_af);
    frac->setFamilyIdName(m_idName);
    return frac;
}

}  // namespace Fractures
