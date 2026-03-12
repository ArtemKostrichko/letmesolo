#pragma once

#include <string>

#include "core/matrix.h"
#include "util/value.h"

namespace report {

    class Step {
    public:
        virtual ~Step() = default;

        virtual std::string name() const = 0;
        virtual util::Value run(const core::Matrix& A) = 0;
    };

} // namespace report