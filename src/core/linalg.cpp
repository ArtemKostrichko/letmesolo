#include "core/linalg.h"

#include <cmath>
#include <utility>

#include "core/constants.h"

namespace core {

    Matrix LinAlgService::rref(const Matrix& matrix) const {
        Matrix result = matrix;

        int pivot_row = 0;

        for (int col = 0; col < result.cols() && pivot_row < result.rows(); ++col) {
            int best_row = pivot_row;
            double best_value = std::abs(result.at(pivot_row, col));

            for (int r = pivot_row + 1; r < result.rows(); ++r) {
                const double current = std::abs(result.at(r, col));
                if (current > best_value) {
                    best_value = current;
                    best_row = r;
                }
            }

            if (best_value < EPS) {
                continue;
            }

            if (best_row != pivot_row) {
                for (int c = 0; c < result.cols(); ++c) {
                    std::swap(result.at(pivot_row, c), result.at(best_row, c));
                }
            }

            const double pivot = result.at(pivot_row, col);
            for (int c = 0; c < result.cols(); ++c) {
                result.at(pivot_row, c) /= pivot;
            }

            for (int r = 0; r < result.rows(); ++r) {
                if (r == pivot_row) {
                    continue;
                }

                const double factor = result.at(r, col);
                if (std::abs(factor) < EPS) {
                    continue;
                }

                for (int c = 0; c < result.cols(); ++c) {
                    result.at(r, c) -= factor * result.at(pivot_row, c);
                    if (std::abs(result.at(r, c)) < EPS) {
                        result.at(r, c) = 0.0;
                    }
                }
            }

            ++pivot_row;
        }

        return result;
    }

    int LinAlgService::rank(const Matrix& matrix) const {
        (void)matrix;
        return 0;
    }

    double LinAlgService::det(const Matrix& matrix) const {
        (void)matrix;
        return 0.0;
    }

    std::optional<Matrix> LinAlgService::inverse(const Matrix& matrix) const {
        (void)matrix;
        return std::nullopt;
    }

} // namespace core