#include "io/matrix_input.h"

#include <cctype>
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

std::vector<double> parseSpaceSeparatedRow(const std::string& line) {
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

core::Matrix buildMatrix(const std::vector<std::vector<double>>& rows) {
    if (rows.empty()) {
        throw core::ParseError("Matrix must contain at least one row");
    }

    const int cols = static_cast<int>(rows.front().size());
    for (int r = 0; r < static_cast<int>(rows.size()); ++r) {
        if (rows[r].empty()) {
            throw core::ParseError("Matrix row " + std::to_string(r + 1) + " is empty");
        }
        if (static_cast<int>(rows[r].size()) != cols) {
            throw core::ParseError(
                "Row " + std::to_string(r + 1) + " has length " +
                std::to_string(rows[r].size()) + ", expected " +
                std::to_string(cols)
            );
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

core::Matrix parseMultilineMatrix(std::istream& in) {
    std::string line;
    std::vector<std::vector<double>> rows;
    int line_number = 1; // строка после открывающей [

    while (std::getline(in, line)) {
        ++line_number;
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        if (line == "]") {
            return buildMatrix(rows);
        }

        try {
            rows.push_back(parseSpaceSeparatedRow(line));
        } catch (const core::ParseError& e) {
            throw core::ParseError(
                "Invalid multiline matrix row at line " + std::to_string(line_number) +
                ": " + e.what()
            );
        }
    }

    throw core::ParseError("Expected closing ']' for multiline matrix");
}

void skipWhitespace(const std::string& s, std::size_t& pos) {
    while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos]))) {
        ++pos;
    }
}

void expectChar(const std::string& s, std::size_t& pos, char expected, const std::string& message) {
    skipWhitespace(s, pos);
    if (pos >= s.size() || s[pos] != expected) {
        throw core::ParseError(message);
    }
    ++pos;
}

double parseNumber(const std::string& s, std::size_t& pos) {
    skipWhitespace(s, pos);

    try {
        std::size_t parsed = 0;
        const double value = std::stod(s.substr(pos), &parsed);
        pos += parsed;
        return value;
    } catch (...) {
        throw core::ParseError("Expected number at position " + std::to_string(pos));
    }
}

std::vector<double> parseBracketRow(const std::string& s, std::size_t& pos, int row_index) {
    expectChar(
        s,
        pos,
        '[',
        "Expected '[' to start row " + std::to_string(row_index)
    );

    std::vector<double> row;

    while (true) {
        row.push_back(parseNumber(s, pos));
        skipWhitespace(s, pos);

        if (pos >= s.size()) {
            throw core::ParseError(
                "Unexpected end of input inside row " + std::to_string(row_index)
            );
        }

        if (s[pos] == ',') {
            ++pos;
            continue;
        }

        if (s[pos] == ']') {
            ++pos;
            break;
        }

        throw core::ParseError(
            "Expected ',' or ']' inside row " + std::to_string(row_index) +
            " at position " + std::to_string(pos)
        );
    }

    if (row.empty()) {
        throw core::ParseError("Matrix row must contain at least one number");
    }

    return row;
}

core::Matrix parseSingleLineMatrix(const std::string& input) {
    std::size_t pos = 0;
    expectChar(input, pos, '[', "Expected '[' to start matrix");

    std::vector<std::vector<double>> rows;
    int row_index = 1;

    while (true) {
        skipWhitespace(input, pos);

        if (pos >= input.size()) {
            throw core::ParseError("Unexpected end of input inside matrix");
        }

        if (input[pos] == ']') {
            ++pos;
            break;
        }

        rows.push_back(parseBracketRow(input, pos, row_index));
        ++row_index;

        skipWhitespace(input, pos);

        if (pos >= input.size()) {
            throw core::ParseError("Unexpected end of input after matrix row");
        }

        if (input[pos] == ',') {
            ++pos;
            continue;
        }

        if (input[pos] == ']') {
            ++pos;
            break;
        }

        throw core::ParseError(
            "Expected ',' or ']' after row at position " + std::to_string(pos)
        );
    }

    skipWhitespace(input, pos);
    if (pos != input.size()) {
        throw core::ParseError(
            "Unexpected trailing characters after matrix at position " +
            std::to_string(pos)
        );
    }

    return buildMatrix(rows);
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
        throw core::ParseError("Expected matrix input, got empty stream");
    }

    if (line == "[") {
        return parseMultilineMatrix(in);
    }

    if (line.starts_with("[[")) {
        return parseSingleLineMatrix(line);
    }

    throw core::ParseError(
        "Unsupported matrix format. Use multiline form '[ ... ]' or single-line form '[[...],[...]]'"
    );
}

} // namespace io