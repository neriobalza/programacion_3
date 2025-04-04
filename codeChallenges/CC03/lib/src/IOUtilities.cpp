#include <IOUtilities.hpp>

std::ostream& operator << (std::ostream& output, const SPair& p) noexcept
{
    output << "(" << std::get<0>(p) << ", " << std::get<1>(p) << ")";
    return output;
}

std::ostream& operator << (std::ostream& out, const BasicStats& stats) noexcept
{
    out << "BasicStats{"
        << "min: " << stats.min
        << ", max: " << stats.max
        << ", mean: " << stats.mean
        << ", var: " << stats.variance
        << ", q1: " << stats.quartiles[0]
        << ", q2: " << stats.quartiles[1]
        << ", q3: " << stats.quartiles[2]
        << ", len: " << stats.len
        << "}";
    return out;
}

std::ostream& operator << (std::ostream& out, const ListPair& lp) noexcept
{
    out << "(" << lp.first << ", " << lp.second << ")";
    return out;
}