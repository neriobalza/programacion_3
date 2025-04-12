/**
    @author: Nerio Balza
    @id: 27777348
*/

#include <Sampler.hpp>

Sampler::Sampler() noexcept
{
    sorted = true;
}

Sampler::Sampler(const std::vector<long> &samples) noexcept
    : Sampler{}
{
    for (long sample : samples)
    {
        this->add_sample(sample);
    }
}

Sampler::Sampler(const Sampler &sampler) noexcept : samples(sampler.samples), sorted(sampler.sorted)
{
}

Sampler::Sampler(Sampler &&sampler) noexcept
    : Sampler{}
{
    this->swap(sampler);
}

Sampler &Sampler::operator=(Sampler sampler) noexcept
{
    this->swap(sampler);
    return *this;
}

void Sampler::swap(Sampler &sampler) noexcept
{
    std::swap(*this, sampler);
}

size_t Sampler::size() const noexcept
{
    return samples.size();
}

double Sampler::mean() const
{
    if (size() == 0)
    {
        throw std::length_error("empty sampler");
    }

    double x = std::accumulate(samples.begin(), samples.end(), 0, [](long acc, long sample)
                               { return acc + sample; });

    return static_cast<double>(x / size());
}

double Sampler::variance() const
{
    double x = mean();
    long double o = std::accumulate(samples.begin(), samples.end(), 0.0, [x](long double acc, long sample)
                                    { return acc + pow((sample - x), 2.0); });
    return o / size();
}

void Sampler::add_sample(long sample) noexcept
{
    if (!samples.empty() && sorted && samples[size() - 1] > sample)
    {
        sorted = false;
    }
    samples.push_back(sample);
}

void Sampler::add_sample(std::istream &in) noexcept
{
    long sample;
    while (in >> sample)
    {
        this->add_sample(sample);
    }
}

long Sampler::get_sample(size_t i)
{
    if (i > size())
    {
        throw std::out_of_range("index out of range");
    }

    sort_samples();

    return samples[i];
}

std::vector<long> Sampler::list() noexcept
{
    sort_samples();
    return samples;
}

BasicStats Sampler::stats()
{
    if (size() == 0)
    {
        throw std::length_error("empty sampler");
    }

    sort_samples();

    double q1 = samples[size() / 4];
    double q2 = size() % 2 == 0 ? (samples[size() / 2.0] + samples[(size() / 2.0) - 1.0]) / 2.0 : samples[size() / 2.0];
    double q3 = samples[(size() * 3) / 4];

    return BasicStats{samples[0], samples[size() - 1], mean(), variance(), q1, q2, q3, size()};
}

std::vector<long> Sampler::get_by_position_range(size_t l, size_t r)
{
    if (l > r)
    {
        throw std::invalid_argument("crossed range");
    }
    if (l > size() || r > size())
    {
        throw std::out_of_range("index out of range");
    }
    sort_samples();

    if (l == r)
    {
        return vector<long>{samples[l]};
    }

    return vector<long>(samples.begin() + l, samples.begin() + r);
}

std::vector<long> Sampler::get_by_key_range(long sl, long sr)
{
    if (sl > sr)
    {
        throw std::invalid_argument("crossed keys");
    }

    sort_samples();

    auto sli = std::upper_bound(samples.begin(), samples.end(), sl);
    auto sri = std::upper_bound(sli, samples.end(), sr);

    return vector<long>(sli, sri);
}

Sampler &Sampler::cut_by_key_range(long sl, long sr)
{
    if (sl > sr)
    {
        throw std::invalid_argument("crossed keys");
    }

    samples = get_by_key_range(sl, sr);

    return *this;
}

Sampler &Sampler::cut_by_position_range(size_t l, size_t r)
{
    if (l > r)
    {
        throw std::invalid_argument("crossed range");
    }
    if (l > size() || r > size())
    {
        throw std::out_of_range("index out of range");
    }
    samples = get_by_position_range(l, r);
    return *this;
}