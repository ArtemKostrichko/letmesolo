#include "report/step_runner.h"

#include <utility>

namespace report {

    void StepRunner::addStep(std::unique_ptr<Step> step) {
        steps_.push_back(std::move(step));
    }

    std::vector<util::Value> StepRunner::runAll(const core::Matrix& matrix) {
        std::vector<util::Value> results;
        results.reserve(steps_.size());

        for (const auto& step : steps_) {
            results.push_back(step->run(matrix));
        }

        return results;
    }

} // namespace report