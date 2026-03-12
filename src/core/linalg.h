#pragma once

#include <optional>

#include "core/matrix.h"

namespace core {

    class LinAlgService {
    public:
        Matrix rref(const Matrix& matrix) const;
        int rank(const Matrix& matrix) const;
        double det(const Matrix& matrix) const;
        std::optional<Matrix> inverse(const Matrix& matrix) const;
    };

} // namespace core