#pragma once

#include <BasicStats.hpp>
#include <algorithm>
#include <numeric>
#include <cmath>

template <typename T>
using vector = std::vector<T>;

class Sampler
{
public:
    Sampler() noexcept;

    Sampler(const std::vector<long> &samples) noexcept;

    Sampler(const Sampler &sampler) noexcept;

    Sampler(Sampler &&sampler) noexcept;

    Sampler &operator=(Sampler sampler) noexcept;

    void swap(Sampler &sampler) noexcept;

    size_t size() const noexcept;

    double mean() const;

    double variance() const;

    void add_sample(long sample) noexcept;

    void add_sample(std::istream &in) noexcept;

    long get_sample(size_t i);

    std::vector<long> list() noexcept;

    BasicStats stats();

    std::vector<long> get_by_position_range(size_t l, size_t r);

    std::vector<long> get_by_key_range(long sl, long sr);

    Sampler &cut_by_key_range(long sl, long sr);

    Sampler &cut_by_position_range(size_t l, size_t r);

private:
    vector<long> samples;
    bool sorted;

    void sort_samples()
    {
        if (!sorted)
        {
            std::sort(samples.begin(), samples.end());
            sorted = true;
        }
    }
};
