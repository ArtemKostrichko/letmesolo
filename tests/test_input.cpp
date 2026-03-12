#include <gtest/gtest.h>

#include "core/errors.h"
#include "core/matrix.h"
#include "io/matrix_input.h"

#include <sstream>
#include <string>

namespace {

void expectMatrixEq(const core::Matrix& actual,
                    const int expectedRows,
                    const int expectedCols,
                    const std::initializer_list<double> expectedValues) {
    ASSERT_EQ(actual.rows(), expectedRows);
    ASSERT_EQ(actual.cols(), expectedCols);
    ASSERT_EQ(static_cast<int>(expectedValues.size()), expectedRows * expectedCols);

    int index = 0;
    for (const double value : expectedValues) {
        const int r = index / expectedCols;
        const int c = index % expectedCols;
        EXPECT_DOUBLE_EQ(actual.at(r, c), value);
        ++index;
    }
}

} // namespace

TEST(MatrixInputTest, ReadsMultilineMatrix) {
    io::MatrixInput input;
    std::istringstream in(
        "[\n"
        "1 2 3\n"
        "4 5 6\n"
        "]\n"
    );

    const core::Matrix matrix = input.read(in);

    expectMatrixEq(matrix, 2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
}

TEST(MatrixInputTest, ReadsSingleLineMatrix) {
    io::MatrixInput input;
    std::istringstream in("[[1,2],[3,4]]");

    const core::Matrix matrix = input.read(in);

    expectMatrixEq(matrix, 2, 2, {1.0, 2.0, 3.0, 4.0});
}

TEST(MatrixInputTest, IgnoresOuterWhitespace) {
    io::MatrixInput input;
    std::istringstream in("   \n\t [[1, 2],[3, 4]]   \n");

    const core::Matrix matrix = input.read(in);

    expectMatrixEq(matrix, 2, 2, {1.0, 2.0, 3.0, 4.0});
}

TEST(MatrixInputTest, ThrowsOnEmptyInput) {
    io::MatrixInput input;
    std::istringstream in("");

    EXPECT_THROW(
        {
            const auto matrix = input.read(in);
            (void)matrix;
        },
        core::ParseError
    );
}

TEST(MatrixInputTest, ThrowsOnJaggedMultilineMatrix) {
    io::MatrixInput input;
    std::istringstream in(
        "[\n"
        "1 2\n"
        "3 4 5\n"
        "]\n"
    );

    EXPECT_THROW(
        {
            const auto matrix = input.read(in);
            (void)matrix;
        },
        core::ParseError
    );
}

TEST(MatrixInputTest, ThrowsOnMissingClosingBracketInMultilineFormat) {
    io::MatrixInput input;
    std::istringstream in(
        "[\n"
        "1 2\n"
        "3 4\n"
    );

    EXPECT_THROW(
        {
            const auto matrix = input.read(in);
            (void)matrix;
        },
        core::ParseError
    );
}

TEST(MatrixInputTest, ThrowsOnMalformedSingleLineMatrix) {
    io::MatrixInput input;
    std::istringstream in("[[1,2],[3,]]");

    EXPECT_THROW(
        {
            const auto matrix = input.read(in);
            (void)matrix;
        },
        core::ParseError
    );
}

TEST(MatrixInputTest, ThrowsOnDifferentRowSizesInSingleLineFormat) {
    io::MatrixInput input;
    std::istringstream in("[[1,2],[3,4,5]]");

    EXPECT_THROW(
        {
            const auto matrix = input.read(in);
            (void)matrix;
        },
        core::ParseError
    );
}