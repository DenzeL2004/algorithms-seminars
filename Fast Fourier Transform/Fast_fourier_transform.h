#ifndef _FAST_FOURIER_TRANSFORM_H_
#define _FAST_FOURIER_TRANSFORM_H_

#include <cmath>
#include <complex.h>

#include "../src/Generals_func/generals.h"
#include "../src/log_info/log_errors.h"


void Poly_multiply (int *array_a, int *array_b, const int size_a, const int size_b, int *result);

void Interpolate (double _Complex *array, const int size, int *result);

void FFT (double _Complex *array, const int size, bool inverse = false);

void Read_numerical_array (FILE* fpin, int array[], const int size);

void Numbers_multiply (const char* num1, const char* num2); 

#endif