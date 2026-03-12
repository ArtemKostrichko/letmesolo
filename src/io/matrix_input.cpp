#include "io/matrix_input.h"

#include <istream>
#include <sstream>
#include <string>
#include <vector>

#include "core/errors.h"

namespace io {

namespace {

std::string trim(const std::string& s) {
    const std::size_t first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}

std::vector<double> parseRow(const std::string& line) {
    std::istringstream iss(line);
    std::vector<double> values;
    double value = 0.0;

    while (iss >> value) {
        values.push_back(value);
    }

    if (values.empty()) {
        throw core::ParseError("Matrix row must contain at least one number");
    }

    iss >> std::ws;
    if (!iss.eof()) {
        throw core::ParseError("Invalid token in matrix row: " + line);
    }

    return values;
}

} // namespace

core::Matrix MatrixInput::read(std::istream& in) const {
    std::string line;

    while (std::getline(in, line)) {
        line = trim(line);
        if (!line.empty()) {
            break;
        }
    }

    if (line.empty()) {
        throw core::ParseError("Expected matrix input");
    }

    if (line != "[") {
        throw core::ParseError("Expected '[' to start multiline matrix");
    }

    std::vector<std::vector<double>> rows;

    while (std::getline(in, line)) {
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        if (line == "]") {
            break;
        }

        rows.push_back(parseRow(line));
    }

    if (rows.empty()) {
        throw core::ParseError("Matrix must contain at least one row");
    }

    const int cols = static_cast<int>(rows.front().size());
    for (const auto& row : rows) {
        if (static_cast<int>(row.size()) != cols) {
            throw core::ParseError("All matrix rows must have the same length");
        }
    }

    core::Matrix result(static_cast<int>(rows.size()), cols);
    for (int r = 0; r < static_cast<int>(rows.size()); ++r) {
        for (int c = 0; c < cols; ++c) {
            result.at(r, c) = rows[r][c];
        }
    }

    return result;
}

} // namespace io