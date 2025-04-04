#pragma once

#include <iostream>
#include <iomanip>

#include <BasicStats.hpp>

#ifdef DEBUG
#define LOG(...) printf(__VA_ARGS__); printf("\n");
#else
#define LOG(...)
#endif

using ListPair = std::pair<std::vector<long>, std::vector<long>>;

std::ostream& operator << (std::ostream& output, const SPair& p) noexcept;

template <typename Sequence>
std::ostream& print_container(std::ostream& output, const Sequence& s) noexcept
{
    output << "[";
    auto it = s.begin();

    if (it != s.end())
    {
        output << *it;
        ++it;
    }

    for ( ; it != s.end(); ++it)
    {
        output << ", " << *it;
    }

    output << "]";
    return output;
}

template <typename T>
std::ostream& operator << (std::ostream& output, const std::vector<T>& s) noexcept
{
    return print_container(output, s);
}

std::ostream& operator << (std::ostream& out, const BasicStats& stats) noexcept;

std::ostream& operator << (std::ostream& out, const ListPair& lp) noexcept;