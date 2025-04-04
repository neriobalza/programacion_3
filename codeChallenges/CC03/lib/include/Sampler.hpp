#pragma once

#include <BasicStats.hpp>

class Sampler
{
public:
    Sampler() noexcept;

    Sampler(const std::vector<long>& samples) noexcept;

    Sampler(const Sampler& sampler) noexcept;

    Sampler(Sampler&& sampler) noexcept;

    Sampler& operator = (Sampler sampler) noexcept;

    void swap(Sampler& sampler) noexcept;

    size_t size() const noexcept;

    double mean() const;

    double variance() const;

    void add_sample(long sample) noexcept;

    void add_sample(std::istream& in) noexcept;

    long get_sample(size_t i) const;

    std::vector<long> list() const noexcept;

    BasicStats stats() const;

    std::vector<long> get_by_position_range(size_t l, size_t r) const;

    std::vector<long> get_by_key_range(long sl, long sr) const;

    std::vector<SPair> get_by_keys(const std::vector<long>& keys) const noexcept;

    Sampler& cut_by_key_range(long sl, long sr);

    Sampler& cut_by_position_range(size_t l, size_t r);

private:
    // Private attributes and method signatures here
};
