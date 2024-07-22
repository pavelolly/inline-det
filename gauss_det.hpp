#pragma once

#include <iostream>

#include "Matrix.hpp"

template<typename NumT>
float gauss_det(const Matrix<NumT>& mat) {
    if (mat.rows() != mat.cols() && mat.rows() != 0) {
        throw std::invalid_argument("float gauss_det(Matrix<> mat): mat is not square matrix");
    }

    Matrix<float> u_mat = mat; // u_mat == upper_triangular

    int sign = 1;
    for (std::size_t i = 0; i < mat.rows(); ++i) {
        float max_elem = std::abs(mat.at(i, i));
        std::size_t max_elem_i = i, max_elem_j = i;
        for (std::size_t mi = i; mi < mat.rows(); ++mi) {
            for (std::size_t mj = (i == mi ? i + 1 : i); mj < mat.cols(); ++mj) {
                if (std::abs(mat.at(mi, mj)) > max_elem) {
                    max_elem = std::abs(mat.at(mi, mj));
                    max_elem_i = mi;
                    max_elem_j = mj;
                }
            }
        }
        if (max_elem == 0) { 
            return 0;
        }

        if (max_elem_i != i) {
            u_mat.swap_rows(i, max_elem_i);
            sign *= -1;
        }
        if (max_elem_j != i) {
            u_mat.swap_cols(i, max_elem_j);
            sign *= -1;
        }

        for (std::size_t k = i + 1; k < u_mat.rows(); ++k) {
            float mult = u_mat.at(k, i) / u_mat.at(i, i);
            if (mult == 0) {
                continue;
            }
            for (std::size_t j = 0; j < mat.cols(); ++j) {
                u_mat.at(k, j) -= mult * u_mat.at(i, j);
            }
        }
    }

    float det = sign;
    for (std::size_t i = 0; i < u_mat.rows(); ++i) {
        det *= u_mat.at(i, i);
    }

    return det;
}
