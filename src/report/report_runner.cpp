#include "report/report_runner.h"

#include "util/value_printer.h"

#include <chrono>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

namespace report {
    namespace {

        class ScopedStepTimer {
        public:
            ScopedStepTimer(std::ostream& out, std::string stepName)
                : out_(out), stepName_(std::move(stepName)), start_(std::chrono::steady_clock::now()) {}

            ~ScopedStepTimer() {
                const auto finish = std::chrono::steady_clock::now();
                const auto elapsed =
                    std::chrono::duration_cast<std::chrono::milliseconds>(finish - start_).count();
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
        // One formatter object is reused in several places:
        // app, report layer and tests.
        // shared_ptr fits this shared ownership model better than unique_ptr.
        for (const auto& step : steps) {
            out << "=== " << step->name() << " ===\n";

            ScopedStepTimer timer(out, step->name());
            const util::Value value = step->run(matrix);

            util::printValue(out, value, printer);
            out << '\n';
        }
    }

} // namespace report