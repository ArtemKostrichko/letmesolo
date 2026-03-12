#include "core/matrix.h"

#include <string>

#include "core/errors.h"

namespace core {

    namespace {
        int indexOf(int cols, int r, int c) {
            return r * cols + c;
        }
    } // namespace

    Matrix::Matrix(int rows, int cols)
        : rows_(rows), cols_(cols), data_(static_cast<std::size_t>(rows * cols), 0.0) {
        if (rows <= 0 || cols <= 0) {
            throw DimensionError("Matrix dimensions must be positive");
        }
    }

    Matrix Matrix::identity(int n) {
        if (n <= 0) {
            throw DimensionError("Identity matrix size must be positive");
        }

        Matrix result(n, n);
        for (int i = 0; i < n; ++i) {
            result.at(i, i) = 1.0;
        }
        return result;
    }

    int Matrix::rows() const {
        return rows_;
    }

    int Matrix::cols() const {
        return cols_;
    }

    double& Matrix::at(int r, int c) {
        if (r < 0 || r >= rows_ || c < 0 || c >= cols_) {
            throw DimensionError(
                "Matrix index out of range: (" + std::to_string(r) + ", " + std::to_string(c) + ")"
            );
        }
        return data_[static_cast<std::size_t>(indexOf(cols_, r, c))];
    }

    double Matrix::at(int r, int c) const {
        if (r < 0 || r >= rows_ || c < 0 || c >= cols_) {
            throw DimensionError(
                "Matrix index out of range: (" + std::to_string(r) + ", " + std::to_string(c) + ")"
            );
        }
        return data_[static_cast<std::size_t>(indexOf(cols_, r, c))];
    }

} // namespace core