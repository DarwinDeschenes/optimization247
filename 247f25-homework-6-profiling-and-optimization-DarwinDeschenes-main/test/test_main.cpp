#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <stdio.h>

extern "C" {
#include "../matrix.h"
#include "../oddinacci.h"
#include "../mat0.h"
#include "../mat1.h"
#include "../mat2.h"
#include "../measure.h"
#include "../transpose.h"
}

#define ODDINACCI_ITERS 40


TEST_CASE("Oddinacci", "[Test]") {
    printf("Running Oddinacci test..\n");
    long val1 = 0;
    double slow = measure(oddinacci, ODDINACCI_ITERS, &val1);

    long val2 = 0;
    double fast = measure(oddinacci_fast, ODDINACCI_ITERS, &val2);

    printf("slow=%lf, fast=%lf\n", slow, fast);
    printf("factor=%f\n", (double) slow / fast);

    REQUIRE(val1 == val2);
    REQUIRE(slow / fast > 100);
    printf("Success!\n");
}

TEST_CASE("Matrix0", "[Mat0]") {
    printf("Running Mat0 test..\n");
    matrix_t mat;
    matrix_init(&mat, 10, 10, 0);

    long val1 = 0;
    double slow = measure_mat(mat0_slow, mat, &val1);

    long val2 = 0;
    double fast = measure_mat(mat0_fast, mat, &val2);

    printf("slow=%lf, fast=%lf\n", slow, fast);
    printf("factor=%f\n", (double) slow / fast);

    REQUIRE(val1 == val2);
    REQUIRE(slow / fast > 10);
    printf("Success!\n");
}

TEST_CASE("Matrix1", "[Mat1]") {
    printf("Running Mat1 test..\n");
    matrix_t mat;
    matrix_init(&mat, 10, 10, 1);

    long val1 = 0;
    double slow = measure_mat(mat1_slow, mat, &val1);

    long val2 = 0;
    double fast = measure_mat(mat1_fast, mat, &val2);

    printf("slow=%f, fast=%f\n", slow, fast);
    printf("factor=%f\n", slow / fast);

    REQUIRE(val1 == val2);
    REQUIRE(slow / fast > 1.5);
    printf("Success!\n");
}

TEST_CASE("Matrix2", "[Mat2]") {
    printf("Running Mat2 test..\n");
    matrix_t mat;
    matrix_init(&mat, 4, 4, 2);

    printf("Calculating slow determinant: ");
    long val1 = 0;
    double slow = measure_mat(mat2_slow, mat, &val1);
    printf("\n");

    printf("Calculating fast determinant: ");
    long val2 = 0;
    double fast = measure_mat(mat2_fast, mat, &val2);
    printf("\n");

    printf("slow=%f, fast=%f\n", slow, fast);
    printf("factor=%f\n", slow / fast);

    REQUIRE(val1 == val2);
    REQUIRE(slow / fast > 2.0);
    printf("Success!\n");
}


#define ROWS 20000
#define COLS 30000


TEST_CASE("Transpose", "[Transpose]") {
    printf("Running Transpose test..\n");

    printf("Creating matrices...\n");
    int* src = (int*) malloc(ROWS * COLS * sizeof(int));
    transpose_fill(src, ROWS, COLS);
    int* dst = (int*) malloc(ROWS * COLS * sizeof(int));
    memset(dst, 0, ROWS * COLS * sizeof(int));

    printf("Calculating slow transpose...\n");
    double slow = measure_transpose(transpose_slow, src, ROWS, COLS, dst);
    printf("Checking that slow transposition is correct...\n");
    REQUIRE(transpose_check(src, ROWS, COLS, dst));
    printf("transpose slow=%f\n", slow);

    printf("Recreating matrices...\n");
    transpose_fill(src, ROWS, COLS);
    memset(dst, 0, ROWS * COLS * sizeof(int));

    printf("Calculating fast transpose...\n");
    double fast = measure_transpose(transpose_fast, src, ROWS, COLS, dst);
    printf("transpose fast=%f\n", fast);
    printf("Checking that fast transposition is correct...\n");
    REQUIRE(transpose_check(src, ROWS, COLS, dst));
    double factor = slow/fast;
    printf("factor=%f\n", factor);
    REQUIRE(factor >= 1.5);

    free(src);
    free(dst);
    printf("Success!\n");
}

/*
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
