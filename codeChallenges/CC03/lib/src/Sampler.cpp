/**
    @author: Nerio Balza
    @id: 27777348
*/

#include <Sampler.hpp>
#include <numeric>
#include <cmath>

Sampler::Sampler() noexcept
{
    sorted = true;
}

Sampler::Sampler(const std::vector<long>& samples) noexcept
    : Sampler{}
{
    for (long sample : samples)
    {
        this->add_sample(sample);
    }
}

Sampler::Sampler(const Sampler& sampler) noexcept : samples_vec(sampler.samples_vec), sorted(sampler.sorted)
{
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
    std::swap(*this, sampler);
}

size_t Sampler::size() const noexcept
{
    return samples_vec.size();
}

double Sampler::mean() const
{
    if(size() == 0){
        throw std::length_error("empty sampler");
    }

    double x = std::accumulate(samples_vec.begin(), samples_vec.end(), 0, [](long acc, long sample)
    { return acc + sample; });
    
    return static_cast<double>(x/size());
}

double Sampler::variance() const
{
    double x = mean();
    double o = std::accumulate(samples_vec.begin(), samples_vec.end(), 0.0, [x](double acc, long sample)
    { return acc + pow((sample - x), 2.0); }); 
    return o/size();
}

void Sampler::add_sample(long sample) noexcept
{
    if(samples_vec.empty()){
        samples_vec.push_back(sample);
        sorted = true;
        return;
    }

    if(sorted && samples_vec[size() - 1] > sample){
        sorted = false;
    }
    samples_vec.push_back(sample);
}

void Sampler::add_sample(std::istream& in) noexcept
{
    long sample;
    while (in >> sample)
    {
        this->add_sample(sample);
    }
}

long Sampler::get_sample(size_t i) 
{
    if(i > size()){
        throw std::out_of_range("index out of range");
    }

    std::sort(samples_vec.begin(), samples_vec.end());

    return samples_vec[i];
}

std::vector<long> Sampler::list() noexcept
{
    if(!sorted){
        std::sort(samples_vec.begin(), samples_vec.end());
        sorted = true;
    }
    return samples_vec;
}

BasicStats Sampler::stats()
{
    if(size() == 0) {
        throw std::length_error("empty sampler");
    }
    if(!sorted){
        std::sort(samples_vec.begin(), samples_vec.end());
        sorted = true;
    }

    double q1 = samples_vec[size()/4];
    double q2 = size() % 2 == 0 ? (samples_vec[size()/2] + samples_vec[(size()/2) - 1])/2  : samples_vec[size()/2];
    double q3 = samples_vec[(size() * 3)/4];

    return BasicStats{samples_vec[0], samples_vec[size() - 1], mean(), variance(), q1, q2, q3, size()};
}

std::vector<long> Sampler::get_by_position_range(size_t l, size_t r)
{
    if(l > r) {
        throw std::invalid_argument("crossed range");
    }
    if(l > size() || r > size() ){
        throw std::out_of_range("index out of range");
    }
    if(!sorted){
        std::sort(samples_vec.begin(), samples_vec.end());
        sorted = true;
    }

    if(l == r){
        return std::vector<long>{samples_vec[l]};
    }

    return std::vector<long>(samples_vec.begin() + l, samples_vec.begin() + r);
}

std::vector<long> Sampler::get_by_key_range(long sl, long sr)
{
    if(sl > sr){
        throw std::invalid_argument("crossed keys");
    }

    std::vector<SPair> spairs = get_by_keys({sl, sr}); 

    if(std::get<1>(spairs[0]) != -1 && std::get<1>(spairs[0]) != -1){    
        return get_by_position_range(std::get<1>(spairs[0]) + 1, std::get<1>(spairs[1]) + 1) ;
    }

    std::vector<long> key_range;

    if(std::get<1>(spairs[0]) != -1 && std::get<1>(spairs[1]) == -1){
        std::copy_if(samples_vec.begin() + std::get<1>(spairs[0]), samples_vec.end(), std::back_inserter(key_range), [sr](long sample)
        { return sample <= sr; });
    }
    else if(std::get<1>(spairs[0]) == -1 && std::get<1>(spairs[1]) != -1){
        std::copy_if(samples_vec.begin(), samples_vec.begin() + std::get<1>(spairs[1]), std::back_inserter(key_range), [sl](long sample)
        { return sample > sl; });
    }
    else{
        std::copy_if(samples_vec.begin(), samples_vec.end(), std::back_inserter(key_range), [sl, sr](long sample)
        { return sample > sl && sample <= sr; });
    }

    return key_range;
}

std::vector<SPair> Sampler::get_by_keys(const std::vector<long>& keys) noexcept
{
    if(!sorted){
        std::sort(samples_vec.begin(), samples_vec.end());
        sorted = true;
    }

    std::vector<long> copy_keys(keys);
    std::sort(copy_keys.begin(), copy_keys.end());
    std::vector<SPair> spair_vec;

    for ( long sample : copy_keys)
    {
        spair_vec.push_back(std::make_tuple(sample, binary_search(sample, 0, size()-1)));
    }

    return spair_vec;
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