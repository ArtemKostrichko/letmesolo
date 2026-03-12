#include "io/matrix_print.h"
#include "util/value_printer.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

namespace {

core::Matrix makeMatrix2x2() {
    core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(1, 0) = 3.0;
    matrix.at(1, 1) = 4.0;
    return matrix;
}

} // namespace

TEST(PrintTest, PrintsMatrixWithFixedPrecision) {
    const core::Matrix matrix = makeMatrix2x2();

    std::ostringstream out;
    io::MatrixPrinter{}.print(out, matrix);

    EXPECT_EQ(
        out.str(),
        "[ 1.0000 2.0000 ]\n"
        "[ 3.0000 4.0000 ]\n");
}

TEST(PrintTest, NormalizesNearZeroValuesToZero) {
    core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 1e-12;
    matrix.at(0, 1) = -1e-12;
    matrix.at(1, 0) = 0.0;
    matrix.at(1, 1) = -0.0;

    std::ostringstream out;
    io::MatrixPrinter{}.print(out, matrix);

    EXPECT_EQ(
        out.str(),
        "[ 0.0000 0.0000 ]\n"
        "[ 0.0000 0.0000 ]\n");
}

TEST(PrintTest, AlignsColumnsByWidestValue) {
    core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 200.0;
    matrix.at(1, 0) = -30.5;
    matrix.at(1, 1) = 4.0;

    std::ostringstream out;
    io::MatrixPrinter{}.print(out, matrix);

    EXPECT_EQ(
        out.str(),
        "[  1.0000 200.0000 ]\n"
        "[ -30.5000   4.0000 ]\n");
}

TEST(PrintTest, PrintsIntegerVariant) {
    std::ostringstream out;
    util::printValue(out, util::Value{42}, io::MatrixPrinter{});

    EXPECT_EQ(out.str(), "42\n");
}

TEST(PrintTest, PrintsDoubleVariant) {
    std::ostringstream out;
    util::printValue(out, util::Value{3.5}, io::MatrixPrinter{});

    EXPECT_EQ(out.str(), "3.5\n");
}

TEST(PrintTest, PrintsStringVariant) {
    std::ostringstream out;
    util::printValue(out, util::Value{std::string("rank = 2")}, io::MatrixPrinter{});

    EXPECT_EQ(out.str(), "rank = 2\n");
}

TEST(PrintTest, PrintsMatrixVariantUsingMatrixPrinter) {
    std::ostringstream out;
    util::printValue(out, util::Value{makeMatrix2x2()}, io::MatrixPrinter{});

    EXPECT_EQ(
        out.str(),
        "[ 1.0000 2.0000 ]\n"
        "[ 3.0000 4.0000 ]\n");
}