#include "Matrix.hpp"
#include "gauss_det.hpp"
// #include "inline_det_7.hpp"

int main() {
    // Matrix<int> mat(3, 3);
    // mat.fill_random();
    Matrix<float> mat(8, 8);
    mat.fill_random();
    
    std::cout << "gauss det: " << gauss_det(mat) << "\n";
    // std::cout << "inline det: " << inline_det_7(mat) << "\n";

    return 0;
}