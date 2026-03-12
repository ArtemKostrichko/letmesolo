#pragma once

#include <iosfwd>

#include "core/matrix.h"

namespace io {

    class MatrixPrinter {
    public:
        void print(std::ostream& out, const core::Matrix& matrix) const;
    };

} // namespace io