#include "core/errors.h"
#include "core/linalg.h"

#include <gtest/gtest.h>

namespace {

core::Matrix make2x2() {
    core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(1, 0) = 3.0;
    matrix.at(1, 1) = 4.0;
    return matrix;
}

TEST(LinAlgTest, ComputesDeterminantForSimpleMatrix) {
    EXPECT_NEAR(core::LinAlgService::det(make2x2()), -2.0, 1e-9);
}

TEST(LinAlgTest, ComputesDeterminantWithRowSwapPivoting) {
    core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 0.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(1, 0) = 3.0;
    matrix.at(1, 1) = 4.0;

    EXPECT_NEAR(core::LinAlgService::det(matrix), -6.0, 1e-9);
}

TEST(LinAlgTest, ThrowsOnDeterminantForNonSquareMatrix) {
    core::Matrix matrix(2, 3);
    EXPECT_THROW(core::LinAlgService::det(matrix), core::DimensionError);
}

TEST(LinAlgTest, ComputesRankForDependentRows) {
    core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(1, 0) = 2.0;
    matrix.at(1, 1) = 4.0;

    EXPECT_EQ(core::LinAlgService::rank(matrix), 1);
}

TEST(LinAlgTest, ComputesFullRankForIndependentRows) {
    core::Matrix matrix(3, 3);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(0, 2) = 3.0;
    matrix.at(1, 0) = 0.0;
    matrix.at(1, 1) = 1.0;
    matrix.at(1, 2) = 4.0;
    matrix.at(2, 0) = 5.0;
    matrix.at(2, 1) = 6.0;
    matrix.at(2, 2) = 0.0;

    EXPECT_EQ(core::LinAlgService::rank(matrix), 3);
}

TEST(LinAlgTest, ComputesInverseForRegularMatrix) {
    const auto inverse = core::LinAlgService::inverse(make2x2());

    ASSERT_TRUE(inverse.has_value());
    EXPECT_NEAR(inverse->at(0, 0), -2.0, 1e-7);
    EXPECT_NEAR(inverse->at(0, 1), 1.0, 1e-7);
    EXPECT_NEAR(inverse->at(1, 0), 1.5, 1e-7);
    EXPECT_NEAR(inverse->at(1, 1), -0.5, 1e-7);
}

TEST(LinAlgTest, ReturnsNulloptForSingularMatrix) {
    core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(1, 0) = 2.0;
    matrix.at(1, 1) = 4.0;

    const auto inverse = core::LinAlgService::inverse(matrix);
    EXPECT_FALSE(inverse.has_value());
}

TEST(LinAlgTest, ThrowsOnInverseForNonSquareMatrix) {
    core::Matrix matrix(2, 3);
    EXPECT_THROW(core::LinAlgService::inverse(matrix), core::DimensionError);
}

TEST(LinAlgTest, ComputesRrefForDependentRows) {
    core::Matrix matrix(2, 3);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(0, 2) = 3.0;
    matrix.at(1, 0) = 2.0;
    matrix.at(1, 1) = 4.0;
    matrix.at(1, 2) = 6.0;

    const core::Matrix result = core::LinAlgService::rref(matrix);

    EXPECT_NEAR(result.at(0, 0), 1.0, 1e-9);
    EXPECT_NEAR(result.at(0, 1), 2.0, 1e-9);
    EXPECT_NEAR(result.at(0, 2), 3.0, 1e-9);
    EXPECT_NEAR(result.at(1, 0), 0.0, 1e-9);
    EXPECT_NEAR(result.at(1, 1), 0.0, 1e-9);
    EXPECT_NEAR(result.at(1, 2), 0.0, 1e-9);
}

TEST(LinAlgTest, ComputesRrefWithPartialPivoting) {
    core::Matrix matrix(2, 3);
    matrix.at(0, 0) = 0.0;
    matrix.at(0, 1) = 1.0;
    matrix.at(0, 2) = 2.0;
    matrix.at(1, 0) = 1.0;
    matrix.at(1, 1) = 3.0;
    matrix.at(1, 2) = 4.0;

    const core::Matrix result = core::LinAlgService::rref(matrix);

    EXPECT_NEAR(result.at(0, 0), 1.0, 1e-9);
    EXPECT_NEAR(result.at(0, 1), 0.0, 1e-9);
    EXPECT_NEAR(result.at(0, 2), -2.0, 1e-9);
    EXPECT_NEAR(result.at(1, 0), 0.0, 1e-9);
    EXPECT_NEAR(result.at(1, 1), 1.0, 1e-9);
    EXPECT_NEAR(result.at(1, 2), 2.0, 1e-9);
}

} // namespace