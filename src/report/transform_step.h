#pragma once

#include "report/step.h"

namespace report {

    class TransformStep : public Step {
    public:
        std::string name() const override;
        util::Value run(const core::Matrix& A) override;
    };

} // namespace report