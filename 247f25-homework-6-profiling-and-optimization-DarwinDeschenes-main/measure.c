#include <time.h>
#include "measure.h"

double measure(long (*func)(long arg), long arg, long* result) {
    clock_t start = clock();
    *result = func(arg);
    clock_t end = clock();
    return end - start;
}

double measure_mat(long (*func)(matrix_t mat), matrix_t mat, long* result) {
    clock_t start = clock();
    *result = func(mat);
    clock_t end = clock();
    return end - start;
}

double measure_transpose(void (*func)(int*, int, int, int*), int* src, int rows, int cols, int* dst) {
    clock_t start = clock();
    func(src, rows, cols, dst);
    clock_t end = clock();
    return end - start;
}
