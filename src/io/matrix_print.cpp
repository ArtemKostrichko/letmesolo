#include "io/matrix_print.h"

#include <cmath>
#include <iomanip>
#include <ostream>

#include "core/constants.h"

namespace io {

    void MatrixPrinter::print(std::ostream& out, const core::Matrix& matrix) const {
        out << "[\n";

        for (int r = 0; r < matrix.rows(); ++r) {
            out << "  ";
            for (int c = 0; c < matrix.cols(); ++c) {
                double value = matrix.at(r, c);
                if (std::abs(value) < core::EPS) {
                    value = 0.0;
                }

                out << std::setw(10) << std::fixed << std::setprecision(core::PRINT_PRECISION) << value;

                if (c + 1 < matrix.cols()) {
                    out << ' ';
                }
            }
            out << '\n';
        }

        out << "]\n";
    }

} // namespace io