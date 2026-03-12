#include "report/report_runner.h"

#include "io/matrix_print.h"
#include "util/value_printer.h"

#include <chrono>
#include <memory>
#include <ostream>

namespace report {
    namespace {

        class ScopedStepTimer {
        public:
            ScopedStepTimer(std::ostream& out, std::string stepName)
                : out_(out), stepName_(std::move(stepName)), start_(std::chrono::steady_clock::now()) {}

            ~ScopedStepTimer() {
                const auto finish = std::chrono::steady_clock::now();
                const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start_).count();
                out_ << "(" << stepName_ << " took " << elapsed << " ms)\n";
            }

        private:
            std::ostream& out_;
            std::string stepName_;
            std::chrono::steady_clock::time_point start_;
        };

    } // namespace

    void runReport(
        const core::Matrix& matrix,
        const std::vector<std::unique_ptr<Step>>& steps,
        std::ostream& out,
        std::shared_ptr<const io::MatrixPrinter> printer) {
        // shared_ptr is justified here because one formatter is reused
        // by several parts of the program: app, report layer and tests.
        // unique_ptr is not suitable because it models exclusive ownership.
        for (const auto& step : steps) {
            out << "=== " << step->name() << " ===\n";
            ScopedStepTimer timer(out, step->name());
            const util::Value value = step->run(matrix);
            util::printValue(out, value, printer);
            out << '\n';
        }
    }

} // namespace report