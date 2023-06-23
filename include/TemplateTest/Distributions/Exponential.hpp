#include <TemplateTest/Distributions/Distribution.hpp>

namespace Distribution {
class Exponential : public Distribution {
public:
    explicit Exponential(double lambda);

    double pdf(double x) const override;
    double cdf(double x) const override;

    double sample() const override;

    double min() const override;
    double max() const override;
    double mean() const override;
    double var() const override;
    double stdev() const override;

protected:
    double m_lambda;
};
}  // namespace Distribution