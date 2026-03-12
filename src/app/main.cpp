#include <exception>
#include <iostream>

#include "core/errors.h"

int main() {
    try {
        std::cout << "matrix_app started\n";
        return 0;
    } catch (const core::ParseError& e) {
        std::cerr << "Parse error: " << e.what() << '\n';
    } catch (const core::DimensionError& e) {
        std::cerr << "Dimension error: " << e.what() << '\n';
    } catch (const core::SingularError& e) {
        std::cerr << "Singular error: " << e.what() << '\n';
    } catch (const core::EvalError& e) {
        std::cerr << "Evaluation error: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Unhandled error: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown error\n";
    }

    return 1;
}