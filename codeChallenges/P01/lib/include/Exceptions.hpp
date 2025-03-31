#pragma once

#include <stdexcept>

class TypeError : public std::runtime_error
{
public:
    TypeError(const std::string& message);
};

class NotFoundError : public std::runtime_error
{
public:
    NotFoundError(const std::string& message);
};

class BadProgram : public std::runtime_error
{
public:
    BadProgram(const std::string& message);
};
