#pragma once

#include "report/step.h"

namespace report {

    class PropertyStep final : public Step {
    public:
        [[nodiscard]] std::string name() const override;
        [[nodiscard]] util::Value run(const core::Matrix& matrix) override;
    };

} // namespace report