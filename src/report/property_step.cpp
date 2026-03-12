#include "report/property_step.h"

#include <sstream>

namespace report {

    std::string PropertyStep::name() const {
        return "Matrix properties";
    }

    util::Value PropertyStep::run(const core::Matrix& matrix) {
        std::ostringstream out;
        out << "property section prepared for:\n";
        out << "- rank\n";
        out << "- determinant\n";
        out << "- inverse\n";
        out << "square matrix: " << (matrix.rows() == matrix.cols() ? "yes" : "no");
        return out.str();
    }

} // namespace report