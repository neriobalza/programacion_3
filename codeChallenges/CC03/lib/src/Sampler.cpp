/**
    @author: Nerio Balza
    @id: 27777348
*/

#include <Sampler.hpp>

Sampler::Sampler() noexcept
{
    // TODO: Remove this comment when you have solved this
}

Sampler::Sampler(const std::vector<long>& samples) noexcept
    : Sampler{}
{
    for (long sample : samples)
    {
        this->add_sample(sample);
    }
}

Sampler::Sampler(const Sampler& sampler) noexcept
{
    // TODO: Remove this comment when you have solved this
}

Sampler::Sampler(Sampler&& sampler) noexcept
    : Sampler{}
{
    this->swap(sampler);
}

Sampler& Sampler::operator = (Sampler sampler) noexcept
{
    this->swap(sampler);
    return *this;
}

void Sampler::swap(Sampler& sampler) noexcept
{
    // TODO: Remove this comment when you have solved this
}

size_t Sampler::size() const noexcept
{
    // TODO: Remove this comment when you have solved this
    return 0;
}

double Sampler::mean() const
{
    // TODO: Remove this comment when you have solved this
    return 0.L;
}

double Sampler::variance() const
{
    // TODO: Remove this comment when you have solved this
    return 0.L;
}

void Sampler::add_sample(long sample) noexcept
{
    // TODO: Remove this comment when you have solved this
}

void Sampler::add_sample(std::istream& in) noexcept
{
    long sample;
    while (in >> sample)
    {
        this->add_sample(sample);
    }
}

long Sampler::get_sample(size_t i) const
{
    // TODO: Remove this comment when you have solved this
    return 0;
}

std::vector<long> Sampler::list() const noexcept
{
    // TODO: Remove this comment when you have solved this
    return std::vector<long>{};
}

BasicStats Sampler::stats() const
{
    // TODO: Remove this comment when you have solved this
    return BasicStats{0, 0, 0., 0., 0., 0., 0., 0};
}

std::vector<long> Sampler::get_by_position_range(size_t l, size_t r) const
{
    // TODO: Remove this comment when you have solved this
    return std::vector<long>{};
}

std::vector<long> Sampler::get_by_key_range(long sl, long sr) const
{
    // TODO: Remove this comment when you have solved this
    return std::vector<long>{};
}

std::vector<SPair> Sampler::get_by_keys(const std::vector<long>& keys) const noexcept
{
    // TODO: Remove this comment when you have solved this
    return std::vector<SPair>{};
}

Sampler& Sampler::cut_by_key_range(long sl, long sr)
{
    // TODO: Remove this comment when you have solved this
    return *this;
}

Sampler& Sampler::cut_by_position_range(size_t l, size_t r)
{
    // TODO: Remove this comment when you have solved this
    return *this;
}