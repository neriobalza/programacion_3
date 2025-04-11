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
    double o = std::accumulate(samples.begin(), samples.end(), 0.0, [x](double acc, long sample)
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
    double q2 = size() % 2 == 0 ? (samples[size() / 2] + samples[(size() / 2) - 1]) / 2 : samples[size() / 2];
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

    long sli = binary_search(sl, 0, size() - 1);
    long sli_delete = (sli == 0 && samples[sli] != sl) ? sli : sli + 1;
    long sri = binary_search(sr, 0, size() - 1);

    vector<long> range = vector<long>(samples.begin() + sli_delete, samples.begin() + (sri + 1));

    return range;
}

std::vector<SPair> Sampler::get_by_keys(const std::vector<long> &keys) noexcept
{
    sort_samples();

    vector<long> copy_keys(keys);
    std::sort(copy_keys.begin(), copy_keys.end());
    vector<SPair> spair_vec;

    for (long sample : copy_keys)
    {
        long pos = binary_search(sample, 0, size() - 1);
        spair_vec.push_back(SPair(sample, samples[pos] == sample ? pos : -1));
    }

    return spair_vec;
}

Sampler &Sampler::cut_by_key_range(long sl, long sr)
{
    samples = get_by_key_range(sl, sr);

    return *this;
}

Sampler &Sampler::cut_by_position_range(size_t l, size_t r)
{
    samples = get_by_position_range(l, r);
    return *this;
}