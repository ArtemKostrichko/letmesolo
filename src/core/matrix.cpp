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

Matrix Matrix::transpose() const {
    Matrix result(cols_, rows_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            result.at(c, r) = at(r, c);
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows_, cols_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            result.at(r, c) = at(r, c) * scalar;
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw DimensionError("Matrix addition requires equal dimensions");
    }

    Matrix result(rows_, cols_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            result.at(r, c) = at(r, c) + other.at(r, c);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw DimensionError("Matrix subtraction requires equal dimensions");
    }

    Matrix result(rows_, cols_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            result.at(r, c) = at(r, c) - other.at(r, c);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw DimensionError("Matrix multiplication requires lhs.cols == rhs.rows");
    }

    Matrix result(rows_, other.cols_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < other.cols_; ++c) {
            double sum = 0.0;
            for (int k = 0; k < cols_; ++k) {
                sum += at(r, k) * other.at(k, c);
            }
            result.at(r, c) = sum;
        }
    }
    return result;
}

} // namespace core