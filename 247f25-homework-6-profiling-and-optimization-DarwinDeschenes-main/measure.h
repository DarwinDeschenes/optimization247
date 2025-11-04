#ifndef MEASURE_H
#define MEASURE_H

#include "matrix.h"

// Measure how long the given function takes to execute
double measure(long (*func)(long), long arg, long* result);

// Measure how long the given function takes to execute
double measure_mat(long (*func)(matrix_t mat), matrix_t mat, long* result);

// Measure how long the transpose function takes to execute
double measure_transpose(void (*func)(int*, int, int, int*), int* src, int rows, int cols, int* dst);

#endif // MEASURE_H
