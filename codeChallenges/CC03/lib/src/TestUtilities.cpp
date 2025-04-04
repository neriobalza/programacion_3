#include <cmath>

#include <TestUtilities.hpp>

bool equal(long x, long y) noexcept
{
    return x == y;
}

bool equal(size_t x, size_t y) noexcept
{
    return x == y;
}

bool equal(float x, float y) noexcept
{
    return fabs(x - y) <= EPSILON;
}

bool equal(double x, double y) noexcept
{
    return fabs(x - y) <= EPSILON;
}

bool equal(const SPair& p1, const SPair& p2) noexcept
{
    return equal(std::get<0>(p1), std::get<0>(p2)) && equal(std::get<1>(p1), std::get<1>(p2));
}

bool equal(const ListPair& lp1, const ListPair& lp2) noexcept
{
    return equal(lp1.first, lp2.first) && equal(lp1.second, lp2.second);
}

bool equal(const BasicStats& s1, const BasicStats& s2) noexcept
{
    return equal(s1.min, s2.min) &&
           equal(s1.max, s2.max) &&
           equal(s1.mean, s2.mean) &&
           equal(s1.variance, s2.variance) &&
           equal(s1.quartiles, s2.quartiles) &&
           equal(s1.len, s2.len);
}