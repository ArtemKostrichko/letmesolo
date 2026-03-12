#pragma once

#include <chrono>
#include <iostream>
#include <string>

namespace report {

    class StepTimer {
    public:
        explicit StepTimer(std::string step_name)
            : step_name_(std::move(step_name)),
              started_at_(std::chrono::steady_clock::now()) {}

        ~StepTimer() {
            const auto finished_at = std::chrono::steady_clock::now();
            const auto elapsed =
                std::chrono::duration_cast<std::chrono::microseconds>(finished_at - started_at_);

            std::cout << "[timer] " << step_name_ << ": " << elapsed.count() << " us\n";
        }

    private:
        std::string step_name_;
        std::chrono::steady_clock::time_point started_at_;
    };

} // namespace report