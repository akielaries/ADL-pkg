/*************************************************************************
 * Testing Mtx class operations
 ************************************************************************/
#include "../../include/linalg/mtx.hpp"
#include "../../include/linalg/mtx_tmpl.hpp"
#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <string>
#include <vector>

using namespace gpmp;
#define TEST_COUT std::cerr << "\033[32m[          ] [ INFO ] \033[0m"

namespace {

// utility test helper function to compare two matrices. used for verifying
// accelerated/non-standard implementations to the simple naive algorithm
// for matrix arithmetic operations
template <typename T>
bool mtx_verif(const std::vector<std::vector<T>> &A,
               const std::vector<std::vector<T>> &B) {
    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        return false;
    }

    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            if (std::abs(A[i][j] - B[i][j]) >
                std::numeric_limits<T>::epsilon()) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool mtx_verif(const std::vector<T> &A, const std::vector<T> &B) {
    int rows = A.size();
    int cols = rows > 0 ? A.size() / rows : 0;

    if (A.size() != B.size()) {
        return false;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (A[i * cols + j] != B[i * cols + j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool mtx_verif(const T *A, const T *B, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (std::abs(A[i * cols + j] - B[i * cols + j]) >
                std::numeric_limits<T>::epsilon()) {
                return false;
            }
        }
    }
    return true;
}

template <typename T> void print_matrix(const T *matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// unit tests for Mtx class methods using Intel intrinsics
#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)

// test case to compare the results of the intrinsics implementation with the
// naive implementation for matrix addition
TEST(ADD_MTX_SMALL_VEC_INT, assert_intel_intrin) {
    int mtx_size = 64;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // define input matrices A and B
    std::vector<std::vector<int>> A(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> B(mtx_size, std::vector<int>(mtx_size));
    // define matrix to store expected result in (from std_mtx_add())
    std::vector<std::vector<int>> expected(mtx_size,
                                           std::vector<int>(mtx_size));
    // define matrix to store actual result (from mtx_add())
    std::vector<std::vector<int>> result(mtx_size, std::vector<int>(mtx_size));

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

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

TEST(ADD_MTX_LARGE_VEC_INT, assert_intel_intrin) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;

    // define input matrices A and B
    std::vector<std::vector<int>> A(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> B(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> expected(mtx_size,
                                           std::vector<int>(mtx_size));
    std::vector<std::vector<int>> result(mtx_size, std::vector<int>(mtx_size));

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

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

TEST(ADD_MTX_SMALL_VEC_DOUBLE, assert_intel_intrin) {
    int mtx_size = 64;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
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

TEST(ADD_MTX_LARGE_VEC_DOUBLE, assert_intel_intrin) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;

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

TEST(ADD_MTX_SMALL_ARR_INT8, assert_intel_intrin) {
    int mtx_size = 400;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // define input matrices A and B
    int8_t *A = new int8_t[mtx_size * mtx_size];
    int8_t *B = new int8_t[mtx_size * mtx_size];
    int8_t *expected = new int8_t[mtx_size * mtx_size];
    int8_t *result = new int8_t[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = static_cast<int8_t>(distribution(gen));
            B[i * mtx_size + j] = static_cast<int8_t>(distribution(gen));
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(ADD_MTX_LARGE_ARR_INT8, assert_intel_intrin) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // define input matrices A and B
    int8_t *A = new int8_t[mtx_size * mtx_size];
    int8_t *B = new int8_t[mtx_size * mtx_size];
    int8_t *expected = new int8_t[mtx_size * mtx_size];
    int8_t *result = new int8_t[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = static_cast<int8_t>(distribution(gen));
            B[i * mtx_size + j] = static_cast<int8_t>(distribution(gen));
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(ADD_MTX_SMALL_ARR_INT16, assert_intel_intrin) {
    int mtx_size = 300;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // define input matrices A and B
    int16_t *A = new int16_t[mtx_size * mtx_size];
    int16_t *B = new int16_t[mtx_size * mtx_size];
    int16_t *expected = new int16_t[mtx_size * mtx_size];
    int16_t *result = new int16_t[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
            B[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(ADD_MTX_LARGE_ARR_INT16, assert_intel_intrin) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // define input matrices A and B
    int16_t *A = new int16_t[mtx_size * mtx_size];
    int16_t *B = new int16_t[mtx_size * mtx_size];
    int16_t *expected = new int16_t[mtx_size * mtx_size];
    int16_t *result = new int16_t[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
            B[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(ADD_MTX_SMALL_ARR_INT, assert_intel_intrin) {
    int mtx_size = 184;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // define input matrices A and B
    int *A = new int[mtx_size * mtx_size];
    int *B = new int[mtx_size * mtx_size];
    int *expected = new int[mtx_size * mtx_size];
    int *result = new int[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
            B[i * mtx_size + j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

    /*
    std::cout << "Matrix A:" << std::endl;
    print_matrix(A, mtx_size, mtx_size);

    std::cout << "Matrix B:" << std::endl;
    print_matrix(B, mtx_size, mtx_size);

    std::cout << "Matrix EXPECTED after addition:" << std::endl;
    print_matrix(expected, mtx_size, mtx_size);

    std::cout << "Matrix RESULT after addition:" << std::endl;
    print_matrix(result, mtx_size, mtx_size);
  */
    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(ADD_MTX_LARGE_ARR_INT, assert_intel_intrin) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // define input matrices A and B
    int *A = new int[mtx_size * mtx_size];
    int *B = new int[mtx_size * mtx_size];
    int *expected = new int[mtx_size * mtx_size];
    int *result = new int[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
            B[i * mtx_size + j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

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
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(ADD_MTX_SMALL_ARR_DOUBLE, assert_intel_intrin) {
    int mtx_size = 64;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // define input matrices A and B
    double *A = new double[mtx_size * mtx_size];
    double *B = new double[mtx_size * mtx_size];
    double *expected = new double[mtx_size * mtx_size];
    double *result = new double[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
            B[i * mtx_size + j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

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
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(ADD_MTX_LARGE_ARR_DOUBLE, assert_intel_intrin) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;

    // define input matrices A and B
    double *A = new double[mtx_size * mtx_size];
    double *B = new double[mtx_size * mtx_size];
    double *expected = new double[mtx_size * mtx_size];
    double *result = new double[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
            B[i * mtx_size + j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

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
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

// TODO: implement tests for large matrices, tests for ints, floats, doubles

// unit tests for Mtx class methods using ARM intrinsics
#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)

TEST(ADD_MTX_SMALL, assert_arm_intrin) {
    int mtx_size = 64;
    // Define input matrices A and B
    std::vector<std::vector<int>> A(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> B(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> expected(mtx_size,
                                           std::vector<int>(mtx_size));
    std::vector<std::vector<int>> result(mtx_size, std::vector<int>(mtx_size));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
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

    // Compare the results
    ASSERT_TRUE(mtx_verif(expected, result));
}

TEST(ADD_MTX_LARGE, assert_arm_intrin) {
    int mtx_size = 1024;
    // Define input matrices A and B
    std::vector<std::vector<int>> A(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> B(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> expected(mtx_size,
                                           std::vector<int>(mtx_size));
    std::vector<std::vector<int>> result(mtx_size, std::vector<int>(mtx_size));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
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

    // Compare the results
    ASSERT_TRUE(mtx_verif(expected, result));
}

#endif

/*
TEST(matrix_print, print_mtx) {
    gpmp::linalg::Matrix<int> mat(3, 4);
    mat.print_mtx();

    std::tuple<gpmp::linalg::Matrix<int>, gpmp::linalg::Matrix<int>> matrices =
        std::make_tuple(gpmp::linalg::Matrix<int>(5, 3),
                        gpmp::linalg::Matrix<int>(6, 4));

    std::get<0>(matrices).print_mtx();
    std::get<1>(matrices).print_mtx();
}*/

} // namespace
