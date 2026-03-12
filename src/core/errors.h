#pragma once

#include <stdexcept>
#include <string>

namespace core {

    class ParseError : public std::runtime_error {
    public:
        explicit ParseError(const std::string& message)
            : std::runtime_error(message) {}
    };

    class DimensionError : public std::runtime_error {
    public:
        explicit DimensionError(const std::string& message)
            : std::runtime_error(message) {}
    };

    class SingularError : public std::runtime_error {
    public:
        explicit SingularError(const std::string& message)
            : std::runtime_error(message) {}
    };

    class EvalError : public std::runtime_error {
    public:
        explicit EvalError(const std::string& message)
            : std::runtime_error(message) {}
    };

} // namespace core