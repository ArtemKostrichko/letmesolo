#include "report/transform_step.h"

namespace report {

    std::string TransformStep::name() const {
        return "transpose";
    }

    util::Value TransformStep::run(const core::Matrix& A) {
        return A.transpose();
    }

} // namespace report