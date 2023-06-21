#pragma once
#include <cmath>
#include <istream>
#include <ostream>
#include <random>

class Random {
public:
    static inline void seed() { s_RandomEngine.seed(std::random_device()()); }
    static inline void seed(uint32_t seed) { s_RandomEngine.seed(seed); }

    static inline int32_t nextInt32() { return s_int32Dist(s_RandomEngine); }

    static inline double nextDouble() { return s_doubleDist(s_RandomEngine); }
    static inline double uniform(double min, double max) {
        return min + (max - min) * nextDouble();
    }
    static inline double gauss() { return s_normalDist(s_RandomEngine); }

    static inline std::mt19937& getEngine() { return s_RandomEngine; }

    static inline void saveState(std::ostream& os) {
        os << s_RandomEngine << '\n'
           << s_int32Dist << '\n'
           << s_doubleDist << '\n'
           << s_normalDist << '\n';
    }

    static inline void loadState(std::istream& os) {
        os >> s_RandomEngine >> s_int32Dist >> s_doubleDist >> s_normalDist;
    }

private:
    static inline thread_local std::mt19937 s_RandomEngine;
    static inline std::uniform_int_distribution<int32_t> s_int32Dist;
    static inline std::uniform_real_distribution<double> s_doubleDist;
    static inline std::normal_distribution<double> s_normalDist;
};