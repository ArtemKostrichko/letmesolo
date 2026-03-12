#include "core/errors.h"
#include "io/matrix_input.h"
#include "io/matrix_print.h"
#include "report/info_step.h"
#include "report/property_step.h"
#include "report/report_runner.h"
#include "report/transform_step.h"

#include <exception>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    try {
        const core::Matrix matrix = io::MatrixInput{}.read(std::cin);

        const auto printer = std::make_shared<const io::MatrixPrinter>();

        std::cout << "=== Input matrix ===\n";
        printer->print(std::cout, matrix);
        std::cout << '\n';

        std::vector<std::unique_ptr<report::Step>> steps;
        steps.push_back(std::make_unique<report::InfoStep>());
        steps.push_back(std::make_unique<report::TransformStep>());
        steps.push_back(std::make_unique<report::PropertyStep>());

        report::runReport(matrix, steps, std::cout, printer);
        return 0;
    } catch (const core::ParseError& error) {
        std::cerr << "Parse error: " << error.what() << '\n';
    } catch (const core::DimensionError& error) {
        std::cerr << "Dimension error: " << error.what() << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
    }

    return 1;
}