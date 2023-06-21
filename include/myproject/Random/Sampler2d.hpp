#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <myproject/Random/Random.hpp>

class Sampler2d {
public:
    Sampler2d(const Eigen::AlignedBox2d& box);

    virtual ~Sampler2d();

    virtual Eigen::Vector2d sample() const = 0;

    double getArea() const;

protected:
    Eigen::AlignedBox2d m_box;
};

class UniformSampler2d : public Sampler2d {
public:
    using Sampler2d::Sampler2d;

    Eigen::Vector2d sample() const override;
};
