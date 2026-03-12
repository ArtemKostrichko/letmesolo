#pragma once

#include "report/step.h"

#include <iosfwd>
#include <memory>
#include <vector>

namespace io {
    class MatrixPrinter;
}

namespace report {

    void runReport(
        const core::Matrix& matrix,
        const std::vector<std::unique_ptr<Step>>& steps,
        std::ostream& out,
        std::shared_ptr<const io::MatrixPrinter> printer);

} // namespace report