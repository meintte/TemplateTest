#pragma once
#include <cmath>
#include <cstdint>

class Domain {
public:
    int32_t nx;
    int32_t ny;

    double Lx;
    double Ly;

    double hx;
    double hy;

    constexpr Domain(int32_t nx_, int32_t ny_, double Lx_, double Ly_)
        : nx(nx_), ny(ny_), Lx(Lx_), Ly(Ly_), hx(Lx_ / nx_), hy(Ly_ / ny_) {}

    [[nodiscard]] constexpr double x(int32_t i) const { return (i + 0.5) * hx; }

    [[nodiscard]] constexpr double y(int32_t j) const { return (j + 0.5) * hy; }

    [[nodiscard]] constexpr int32_t i(double x) const {
        return static_cast<int32_t>(x / hx);
    }
    [[nodiscard]] constexpr int32_t j(double y) const {
        return static_cast<int32_t>(y / hy);
    }
};