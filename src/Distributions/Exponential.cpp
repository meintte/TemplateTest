#include <TemplateTest/Distributions/Exponential.hpp>
#include <TemplateTest/Random/Random.hpp>

namespace Distribution {

Exponential::Exponential(double lambda)
    : Distribution({0, std::numeric_limits<double>::infinity()}),
      m_lambda{lambda} {}

double Exponential::pdf(double x) const {
    if (x < m_support.first || x > m_support.second) {
        return 0.0;
    }
    return m_lambda * std::exp(-m_lambda * x);
};

double Exponential::cdf(double x) const {
    if (x < m_support.first) {
        return 0.0;
    }
    return 1.0 - std::exp(-m_lambda * x);
}

double Exponential::sample() const {
    return -std::log(Random::nextDouble()) / m_lambda;
}

double Exponential::min() const { return m_support.first; }
double Exponential::max() const { return m_support.second; }
double Exponential::mean() const { return 1.0 / m_lambda; }
double Exponential::var() const { return 1.0 / (m_lambda * m_lambda); }
double Exponential::stdev() const { return 1.0 / m_lambda; }

}  // namespace Distribution