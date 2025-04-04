#include <BasicStats.hpp>

BasicStats::BasicStats(long _min, long _max, double _mean, double _variance,
                       double _q1, double _q2, double _q3, size_t _len) noexcept
    : min{_min}, max{_max}, mean{_mean}, variance{_variance},
      quartiles{{_q1, _q2, _q3}}, len{_len}
{
    // empty
}
