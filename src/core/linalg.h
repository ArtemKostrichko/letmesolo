#pragma once

#include "core/matrix.h"

#include <optional>

namespace core {

    class LinAlgService {
    public:
        [[nodiscard]] static Matrix rref(Matrix matrix);
        [[nodiscard]] static int rank(Matrix matrix);
        [[nodiscard]] static double det(Matrix matrix);
        [[nodiscard]] static std::optional<Matrix> inverse(const Matrix& matrix);
    };

} // namespace core