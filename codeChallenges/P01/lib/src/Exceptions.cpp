#include <Exceptions.hpp>

TypeError::TypeError(const std::string& message)
    : std::runtime_error{message}
{
    // empty
}

NotFoundError::NotFoundError(const std::string& message)
    : std::runtime_error{message}
{
    // empty
}

BadProgram::BadProgram(const std::string& message)
    : std::runtime_error{message}
{
    // empty
}
