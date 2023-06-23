#include <TemplateTest/Distributions/Dirac.hpp>

namespace Distribution {

Dirac::Dirac(double x, double tol) : Distribution({x, x}), m_tolerance{tol} {}

double Dirac::pdf(double x) const {
    if (std::abs(x - m_support.first) < m_tolerance) {
        return 1.0;  // TODO: maybe return infinity?
    }
    return 0.0;
}
double Dirac::cdf(double x) const {
    // TODO: include tolerance? don't 0.5?
    if (x < m_support.first) {
        return 0.0;
    }
    if (x > m_support.first) {
        return 1.0;
    }
    return 0.5;
}

double Dirac::sample() const { return m_support.first; }

double Dirac::min() const { return m_support.first; }
double Dirac::max() const { return m_support.first; }
double Dirac::mean() const { return m_support.first; }
double Dirac::var() const { return 0.0; }
double Dirac::stdev() const { return 0.0; }

}  // namespace Distribution
