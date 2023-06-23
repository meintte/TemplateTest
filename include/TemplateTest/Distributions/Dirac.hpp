#pragma once

#include <TemplateTest/Distributions/Distribution.hpp>

namespace Distribution {

class Dirac : public Distribution {
public:
    // Non zero response for test < expected +- tol
    explicit Dirac(double x,
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
    double m_tolerance = 0.0;
};

}  // namespace Distribution