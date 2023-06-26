#include <TemplateTest/Random/Random.hpp>
#include <TemplateTest/Random/Sampler2d.hpp>

Sampler2d::Sampler2d(const Eigen::AlignedBox2d& box) : m_box(box) {}

Sampler2d::~Sampler2d() = default;

double Sampler2d::getArea() const { return m_box.volume(); }

Eigen::Vector2d UniformSampler2d::sample() const {
    const auto& boxMin = m_box.min();
    const auto& boxMax = m_box.max();
    return {Random::uniform(boxMin.x(), boxMax.x()),
            Random::uniform(boxMin.y(), boxMax.y())};

}
