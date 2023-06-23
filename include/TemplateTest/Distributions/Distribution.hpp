#pragma once
#include <cmath>
#include <limits>
#include <utility>

namespace Distribution {
template <typename T = double>
using Range = std::pair<T, T>;

/*
 * maybe add the following (TODO):
 *
 * - in Distribution register the distribution name/type with:
 *      enum Type {UNKNOWN, Delta, Uniform, ...}
 *      constexpr Distribution(Type type = Type::UNKNOWN) : m_type{type} {}
 * - This allows for use in switch and comparisons
 *      constexpr operator Type() const { return m_type; }
 * - Prevent usage: if(distribution)
 *      explicit operator bool() const = delete;
 * - rethink the range/support thing
 * 
 */

class Distribution {
public:
    Distribution(
        const Range<double>& support,
        const Range<double>& range = {-std::numeric_limits<double>::infinity(),
                                      std::numeric_limits<double>::infinity()})
        : m_range{range}, m_support{support} {}

    virtual ~Distribution() = default;

    virtual double pdf(double x) const = 0;
    virtual double cdf(double x) const = 0;

    virtual double sample() const = 0;

    virtual double min() const = 0;
    virtual double max() const = 0;
    virtual double mean() const = 0;
    virtual double var() const = 0;
    virtual double stdev() const = 0;

protected:
    Range<double> m_range;  // the inverval subset of (-infinity,infinity) where
                            // the distribution is defined for
    Range<double> m_support;  // the interval where the distribution is nonzero
};

}  // namespace Distribution
