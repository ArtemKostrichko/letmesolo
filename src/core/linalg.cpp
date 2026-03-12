#include "core/linalg.h"

#include "core/constants.h"
#include "core/errors.h"

#include <algorithm>
#include <cmath>

namespace core {
namespace {

int findPivotRow(const Matrix& matrix, const int startRow, const int col) {
    int pivot = startRow;
    double best = std::abs(matrix.at(startRow, col));
    for (int r = startRow + 1; r < matrix.rows(); ++r) {
        const double candidate = std::abs(matrix.at(r, col));
        if (candidate > best) {
            best = candidate;
            pivot = r;
        }
    }
    return pivot;
}

void swapRows(Matrix& matrix, const int r1, const int r2) {
    if (r1 == r2) {
        return;
    }
    for (int c = 0; c < matrix.cols(); ++c) {
        std::swap(matrix.at(r1, c), matrix.at(r2, c));
    }
}

bool rowIsZero(const Matrix& matrix, const int row) {
    for (int c = 0; c < matrix.cols(); ++c) {
        if (!isNearlyZero(matrix.at(row, c))) {
            return false;
        }
    }
    return true;
}

} // namespace

Matrix LinAlgService::rref(Matrix matrix) {
    int pivotRow = 0;

    for (int col = 0; col < matrix.cols() && pivotRow < matrix.rows(); ++col) {
        const int bestRow = findPivotRow(matrix, pivotRow, col);
        if (isNearlyZero(matrix.at(bestRow, col))) {
            continue;
        }

        swapRows(matrix, pivotRow, bestRow);

        const double pivot = matrix.at(pivotRow, col);
        for (int c = 0; c < matrix.cols(); ++c) {
            matrix.at(pivotRow, c) /= pivot;
            if (isNearlyZero(matrix.at(pivotRow, c))) {
                matrix.at(pivotRow, c) = 0.0;
            }
        }

        for (int r = 0; r < matrix.rows(); ++r) {
            if (r == pivotRow) {
                continue;
            }

            const double factor = matrix.at(r, col);
            if (isNearlyZero(factor)) {
                continue;
            }

            for (int c = 0; c < matrix.cols(); ++c) {
                matrix.at(r, c) -= factor * matrix.at(pivotRow, c);
                if (isNearlyZero(matrix.at(r, c))) {
                    matrix.at(r, c) = 0.0;
                }
            }
        }

        ++pivotRow;
    }

    return matrix;
}

int LinAlgService::rank(Matrix matrix) {
    matrix = rref(std::move(matrix));

    int result = 0;
    for (int r = 0; r < matrix.rows(); ++r) {
        if (!rowIsZero(matrix, r)) {
            ++result;
        }
    }
    return result;
}

double LinAlgService::det(Matrix matrix) {
    if (matrix.rows() != matrix.cols()) {
        throw DimensionError("determinant is defined only for square matrices");
    }

    double sign = 1.0;
    double determinant = 1.0;
    const int n = matrix.rows();

    for (int col = 0; col < n; ++col) {
        const int pivotRow = findPivotRow(matrix, col, col);
        if (isNearlyZero(matrix.at(pivotRow, col))) {
            return 0.0;
        }

        if (pivotRow != col) {
            swapRows(matrix, pivotRow, col);
            sign *= -1.0;
        }

        const double pivot = matrix.at(col, col);
        determinant *= pivot;

        for (int r = col + 1; r < n; ++r) {
            const double factor = matrix.at(r, col) / pivot;
            if (isNearlyZero(factor)) {
                continue;
            }

            for (int c = col; c < n; ++c) {
                matrix.at(r, c) -= factor * matrix.at(col, c);
                if (isNearlyZero(matrix.at(r, c))) {
                    matrix.at(r, c) = 0.0;
                }
            }
        }
    }

    const double result = determinant * sign;
    return isNearlyZero(result) ? 0.0 : result;
}

std::optional<Matrix> LinAlgService::inverse(const Matrix& matrix) {
    if (matrix.rows() != matrix.cols()) {
        throw DimensionError("inverse is defined only for square matrices");
    }

    const int n = matrix.rows();
    Matrix augmented(n, 2 * n);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            augmented.at(r, c) = matrix.at(r, c);
        }
        for (int c = 0; c < n; ++c) {
            augmented.at(r, n + c) = (r == c ? 1.0 : 0.0);
        }
    }

    augmented = rref(std::move(augmented));

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            const double expected = (r == c ? 1.0 : 0.0);
            if (std::abs(augmented.at(r, c) - expected) > 1e-7) {
                return std::nullopt;
            }
        }
    }

    Matrix inverseMatrix(n, n);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            inverseMatrix.at(r, c) = augmented.at(r, n + c);
            if (isNearlyZero(inverseMatrix.at(r, c))) {
                inverseMatrix.at(r, c) = 0.0;
            }
        }
    }

    return inverseMatrix;
}

} // namespace core