#pragma once

#include <IOUtilities.hpp>

static constexpr double EPSILON{0.000001};

bool equal(long x, long y) noexcept;

bool equal(size_t x, size_t y) noexcept;

bool equal(double x, double y) noexcept;

bool equal(const SPair& p1, const SPair& p2) noexcept;

template <typename Sequence>
bool equal(const Sequence& s1, const Sequence& s2) noexcept
{
    if (s1.size() != s2.size())
    {
        return false;
    }

    auto a = s1.begin();
    auto b = s2.begin();

    for ( ; a != s1.end(); ++a, ++b)
    {
        if (!equal(*a, *b))
        {
            return false;
        }
    }

    return true;
}

bool equal(const BasicStats& s1, const BasicStats& s2) noexcept;

bool equal(const ListPair& lp1, const ListPair& lp2) noexcept;

template <typename T>
void assert_equal(const T& current, const T& expected) noexcept
{
    if (!equal(current, expected))
    {
        std::cerr << "Test failed!\n";
        std::cerr << "Current value: " << current << std::endl;
        std::cerr << "Expected value: " << expected << std::endl;
        abort();
    }

    std::cout << "Test ok!\n";
}

template <class Exception, class Method, typename... Args>
void assert_throw_exception(const Method& method, Args&& ...args)
{
    try
    {
        method(args...);
        std::cerr << "Test failed!\n";
        std::cerr << "No exception thrown\n";
    }
    catch (Exception)
    {
        std::cout << "Test ok!\n";
        return;
    }
    catch (...)
    {
        std::cerr << "Test failed!\n";
        std::cerr << "Another exception type was thrown\n";
    }

    abort();
}
