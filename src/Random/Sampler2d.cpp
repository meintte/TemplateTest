#include <myproject/Random/Random.hpp>
#include <myproject/Random/Sampler2d.hpp>

Sampler2d::Sampler2d(const Eigen::AlignedBox2d& box) : m_box(box) {}

Sampler2d::~Sampler2d() = default;

double Sampler2d::getArea() const { return m_box.volume(); }

Eigen::Vector2d UniformSampler2d::sample() const {
    return {Random::uniform(m_box.min().x(), m_box.max().x()),
            Random::uniform(m_box.min().y(), m_box.max().y())};
}
