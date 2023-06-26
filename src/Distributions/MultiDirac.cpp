#include <TemplateTest/Distributions/MultiDirac.hpp>
#include <TemplateTest/Random/Random.hpp>
#include <algorithm>
#include <ranges>
#include <stdexcept>

namespace Distribution {

MultiDirac::MultiDirac(std::vector<double> x,
                       const std::vector<double>& weights, double tol)
    : Distribution({-std::numeric_limits<double>::infinity(),
                    std::numeric_limits<double>::infinity()}),
      m_x(std::move(x)),
      m_tolerance(tol) {
    // Check array shapes
    if (m_x.size() != weights.size()) {
        throw std::invalid_argument("x and weights must have the same size");
    }
    if (m_x.empty()) {
        throw std::invalid_argument(
            "x and weights must have at least one element");
    }

    // create a discrete distribution with the weights (normalized by sum)
    m_discDistribution =
        std::discrete_distribution<uint32_t>(weights.begin(), weights.end());
}

double MultiDirac::pdf(double x) const {
    auto it = std::ranges::find_if(
        m_x, [&](double val) { return std::abs(val - x) < m_tolerance; });
    if (it != m_x.end()) {
        return m_discDistribution.probabilities()[static_cast<size_t>(
            std::ranges::distance(m_x.begin(), it))];
    }
    return 0.0;
}

double MultiDirac::cdf(double x) const {
    if (x < MultiDirac::min()) {
        return 0.0;
    }
    if (x >= MultiDirac::max()) {
        return 1.0;
    }

    const auto& probs = m_discDistribution.probabilities();
    double sum = 0.0;
    for (size_t i = 0; i < m_x.size(); ++i) {
        if (m_x[i] <= x + m_tolerance) {
            sum += probs[i];
        }
    }
    // TODO: cpp23
    // for (auto [xi, prob] : std::views::zip(m_x, probs)) {
    //     if (std::abs(xi - x) <= m_tolerance) {
    //         sum += prob;
    //     }
    // }

    return sum;
}

double MultiDirac::sample() const {
    return m_x[m_discDistribution(Random::getEngine())];
}

double MultiDirac::min() const { return m_x[m_discDistribution.min()]; }

double MultiDirac::max() const { return m_x[m_discDistribution.max()]; }

double MultiDirac::mean() const {
    auto prob = m_discDistribution.probabilities();
    double mean = 0.0;
    for (size_t i = 0; i < m_x.size(); ++i) {
        mean += prob[i] * m_x[i];
    }
    // TODO: cpp23
    // for (auto [xi, pi] : std::views::zip(m_x, prob)) {
    //     mean += pi * xi;
    // }
    return mean;
}

double MultiDirac::var() const {
    auto prob = m_discDistribution.probabilities();
    double mean = 0.0;
    double mean2 = 0.0;
    for (size_t i = 0; i < m_x.size(); ++i) {
        mean += prob[i] * m_x[i];
        mean2 += prob[i] * m_x[i] * m_x[i];
    }
    // TODO: cpp23
    // for (auto [xi, pi] : std::views::zip(m_x, prob)) {
    //     mean += pi * xi;
    //     mean2 += pi * xi * xi;
    // }
    return mean2 - mean * mean;
}

double MultiDirac::stdev() const { return std::sqrt(var()); }

}  // namespace Distribution
