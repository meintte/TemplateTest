#pragma once
#include <TemplateTest/Distributions/Distribution.hpp>
#include <random>

namespace Distribution {
class MultiDirac : public Distribution {
public:
    // Non zero response for test < expected +- tol
    MultiDirac(std::vector<double> x, const std::vector<double>& weights,
               double tol = std::numeric_limits<double>::epsilon());

    double pdf(double x) const override;
    double cdf(double x) const override;

    double sample() const override;

    double min() const override;
    double max() const override;
    double mean() const override;
    double var() const override;
    double stdev() const override;

protected:
    std::vector<double> m_x;
    double m_tolerance = 0.0;
    mutable std::discrete_distribution<uint32_t> m_discDistribution;
};
}  // namespace Distribution
