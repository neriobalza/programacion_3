#pragma once

#include <Types.hpp>

enum class Quartile : size_t
{
    Q1,
    Q2,
    Q3,
    NumQuartiles
};

struct BasicStats
{
    long min;
    long max;
    double mean;
    double variance;
    std::vector<double> quartiles;
    size_t len;

    BasicStats(long _min, long _max, double _mean, double _variance,
               double _q1, double _q2, double _q3, size_t _len) noexcept;
};