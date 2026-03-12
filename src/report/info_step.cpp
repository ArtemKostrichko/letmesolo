#include "report/info_step.h"

#include <string>

namespace report {

    std::string InfoStep::name() const {
        return "info";
    }

    util::Value InfoStep::run(const core::Matrix& A) {
        const bool is_square = A.rows() == A.cols();
        const int elements = A.rows() * A.cols();

        return "rows=" + std::to_string(A.rows()) +
               ", cols=" + std::to_string(A.cols()) +
               ", square=" + std::string(is_square ? "yes" : "no") +
               ", elements=" + std::to_string(elements);
    }

} // namespace report