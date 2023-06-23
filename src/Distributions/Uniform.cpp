#include <TemplateTest/Distributions/Uniform.hpp>
#include <TemplateTest/Random/Random.hpp>

namespace Distribution {

Uniform::Uniform(double leftBound, double rightBound)
    : Distribution(
          {std::min(leftBound, rightBound), std::max(leftBound, rightBound)}) {}

double Uniform::pdf(double x) const {
    if (x < m_support.first || x > m_support.second) {
        return 0.0;
    }
    return 1.0 / (m_support.second - m_support.first);
};

double Uniform::cdf(double x) const {
    if (x < m_support.first) {
        return 0.0;
    }
    if (x > m_support.second) {
        return 1.0;
    }
    return (x - m_support.first) / (m_support.second - m_support.first);
}

double Uniform::sample() const {
    return Random::uniform(m_support.first, m_support.second);
}

double Uniform::min() const { return m_support.first; }
double Uniform::max() const { return m_support.second; }
double Uniform::mean() const {
    return 0.5 * (m_support.first + m_support.second);
}
double Uniform::var() const {
    return (m_support.second - m_support.first) *
           (m_support.second - m_support.first) / 12.0;
}
double Uniform::stdev() const {
    return 0.5 * (m_support.second - m_support.first) / std::sqrt(3.0);
}

}  // namespace Distribution