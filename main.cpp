#include <ctime>

#include "Matrix.hpp"
#include "gauss_det.hpp"

#define MAT_SIZE 7
#define inline_det inline_det_7
#include "inline_det_7.hpp"

#define EXEC_COUNT 10000

int main() {
    // Matrix<int> mat(3, 3);
    // mat.fill_random();
    Matrix<float> mat(MAT_SIZE, MAT_SIZE);
    mat.fill_random();
    
    clock_t t1 = clock();
    for (int i = 0; i < EXEC_COUNT; ++i) {
        float det = gauss_det(mat);
        if (i == EXEC_COUNT - 1) {
            std::cout << "gauss det: " << det << "\n";
        }
    }
    clock_t t2 = clock();
    std::cout << "Average time: " << std::fixed << (float)(t2 - t1) / CLOCKS_PER_SEC / EXEC_COUNT << "\n\n";

    t1 = clock();
    for (int i = 0; i < EXEC_COUNT; ++i) {
        float det = inline_det(mat);
        if (i == EXEC_COUNT - 1) {
            std::cout << "inline det: " << det << "\n";
        }
    }
    t2 = clock();
    std::cout << "Average time: " << std::fixed << (float)(t2 - t1) / CLOCKS_PER_SEC / EXEC_COUNT << "\n\n";

    return 0;
}