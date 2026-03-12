#pragma once

#include <vector>

namespace core {

    class Matrix {
    public:
        Matrix(int rows, int cols);

        static Matrix identity(int n);

        int rows() const;
        int cols() const;

        double& at(int r, int c);
        double at(int r, int c) const;

    private:
        int rows_;
        int cols_;
        std::vector<double> data_;
    };

} // namespace core