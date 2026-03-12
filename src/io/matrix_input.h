#pragma once

#include <iosfwd>

#include "core/matrix.h"

namespace io {

    class MatrixInput {
    public:
        core::Matrix read(std::istream& in) const;
    };

} // namespace io