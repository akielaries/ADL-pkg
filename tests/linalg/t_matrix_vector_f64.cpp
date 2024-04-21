/*************************************************************************
 * Testing Mtx class operations
 ************************************************************************/
#include "t_matrix.hpp"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <openGPMP/linalg/mtx.hpp>
#include <openGPMP/linalg/mtx_tmpl.hpp>
#include <string>
#include <vector>

using namespace gpmp;
#define TEST_COUT std::cerr << "\033[32m[          ] [ INFO ] \033[0m"
#define INFO_COUT                                                              \
    std::cerr << "\033[32m[          ] [ INFO ] \033[0m\033[1;34m\033[1m"
namespace {

TEST(MatrixVectorTestF64, AdditionComparisonSmall) {
    INFO_COUT << "MATRIX (as Vectors) FLOAT64" << std::endl;

    int mtx_size = 64;
    // define input matrices A and B
    std::vector<std::vector<double>> A(mtx_size, std::vector<double>(mtx_size));
    std::vector<std::vector<double>> B(mtx_size, std::vector<double>(mtx_size));
    // define matrix to store expected result in (from std_mtx_add())
    std::vector<std::vector<double>> expected(mtx_size,
                                              std::vector<double>(mtx_size));
    // define matrix to store actual result (from mtx_add())
    std::vector<std::vector<double>> result(mtx_size,
                                            std::vector<double>(mtx_size));

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result);

    /*
        std::cout << "Matrix EXPECTED after addition:" << std::endl;
        for (int i = 0; i < mtx_size; ++i) {
            for (int j = 0; j < mtx_size; ++j) {
                std::cout << expected[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix RESULT after addition:" << std::endl;
        for (int i = 0; i < mtx_size; ++i) {
            for (int j = 0; j < mtx_size; ++j) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    */

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result));
}

TEST(MatrixVectorTestF64, AdditionComparisonLarge) {
    int mtx_size = 1024;

    // define input matrices A and B
    std::vector<std::vector<double>> A(mtx_size, std::vector<double>(mtx_size));
    std::vector<std::vector<double>> B(mtx_size, std::vector<double>(mtx_size));
    std::vector<std::vector<double>> expected(mtx_size,
                                              std::vector<double>(mtx_size));
    std::vector<std::vector<double>> result(mtx_size,
                                            std::vector<double>(mtx_size));

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result);

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result));
}

TEST(MatrixVectorTestF64, AdditionPerformanceComparison) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size      : " << mtx_size << std::endl;

    // define input matrices A and B
    std::vector<std::vector<double>> A(mtx_size, std::vector<double>(mtx_size));
    std::vector<std::vector<double>> B(mtx_size, std::vector<double>(mtx_size));
    std::vector<std::vector<double>> expected(mtx_size,
                                              std::vector<double>(mtx_size));
    std::vector<std::vector<double>> result(mtx_size,
                                            std::vector<double>(mtx_size));

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    auto start_std = std::chrono::high_resolution_clock::now();

    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected);

    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    auto start_intrin = std::chrono::high_resolution_clock::now();

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result);
    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    TEST_COUT << "INTRINSIC Matrix Addition Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Addition Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result));
}
} // namespace
