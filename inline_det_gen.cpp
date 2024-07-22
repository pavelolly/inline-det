#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <sstream>

std::size_t permutation_inversions(const std::vector<int> &p) {
    std::size_t count = 0;
    for (int i = 0; i < p.size() - 1; ++i) {
        for (int j = i + 1; j < p.size(); ++j) {
            if (p[i] > p[j]) {
                ++count;
            }
        }
    }
    return count;
}

void generate_inline_det_file(const char *filename, std::size_t mat_size) {
    std::ofstream os(filename);
    if (!os) {
        std::cerr << "Could not open file '" << filename << "'" << std::endl;
        return;
    }
    if (mat_size == 0) {
        std::cerr << "Cant't generate for mat_size = 0" << std::endl;
        return;
    }
    os << "\n";
    os << "#pragma once\n";
    os << "#include <iostream>\n";
    os << "\n";
    os << "#include \"Matrix.hpp\"\n";
    os << "\n";
    os << "\n/* GENERATED with mat size to be " << mat_size << "*/\n\n";
    os << "template<typename NumT>\n";
    os << "float inline_det_" << mat_size << "(const Matrix<NumT>& mat) {\n";
    os << "    if (mat.rows() != mat.cols() && mat.rows() != " << mat_size << ") {\n";
    os << "         throw std::invalid_argument(\"float inline_det(Matrix<> mat): mat is not square matrix or mat_size is not what expected\");\n";
    os << "    }\n";
    os << "\n";
    os << "    float det = ";

    std::vector<int> permutation(mat_size);
    std::iota(permutation.begin(), permutation.end(), 0);

    bool first = true;
    do {
        std::size_t invs = permutation_inversions(permutation);
        if (!first) {
            os << "                " << (invs % 2 == 0 ? "+" : "-");
        }
        first = false;
        for (int i = 0; i < mat_size; ++i) {
            os << "mat[" << i << "][" << permutation[i] << "]";
            if (i != mat_size - 1) {
                os << "*";
            }
        }
        os << "\n";
    } while (std::next_permutation(permutation.begin(), permutation.end()));
    os << "    ;\n";
    os << "    return det;\n";
    os << "}";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: gen <matrix_size>" << std::endl;
        return 1;
    }

    int size = std::atoi(argv[1]);
    if (size == 0) {
        std::cerr << "Usage: gen <matrix_size>\n";
        std::cerr << "Where: matrix_size is a positive integer" << std::endl;
        return 1;
    }

    const char *filename = ("inline_det_" + std::to_string(size) + ".hpp").c_str();
    generate_inline_det_file(filename, size);
    return 0;
}