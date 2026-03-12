#pragma once

#include <memory>
#include <vector>

#include "core/matrix.h"
#include "report/step.h"
#include "util/value.h"

namespace report {

    class StepRunner {
    public:
        void addStep(std::unique_ptr<Step> step);
        std::vector<util::Value> runAll(const core::Matrix& matrix);

    private:
        std::vector<std::unique_ptr<Step>> steps_;
    };

} // namespace report