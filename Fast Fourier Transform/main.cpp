#include <stdio.h>
#include <string.h>

#include <math.h>
#include <complex.h>

#include "../src/log_info/log_errors.h"
#include "../src/Generals_func/generals.h"

#include "Fast_fourier_transform.h"

int main ()
{

    char *num1 = "12365", *num2 = "8526486556";

    Numbers_multiply (num1, num2);



    int size_polynomial_a = 0, size_polynomial_b = 0;

    int scan_result = scanf ("%d%d", &size_polynomial_a, &size_polynomial_b);

    if (scan_result != 2)
    {
        Err_report ("Array size were calculated incorrectly\n");
        return EXIT_FAILURE;
    }

    if (size_polynomial_a <= 0 || size_polynomial_b <= 0)
    {
        Err_report ("incorrect array sizes, size_a = %d, size_b = %d\n", 
                                    size_polynomial_a, size_polynomial_b);
        return EXIT_FAILURE;
    }

    int array_a[size_polynomial_a] = {};
    int array_b[size_polynomial_b] = {};

    Read_numerical_array (stdin, array_a, size_polynomial_a);
    Read_numerical_array (stdin, array_b, size_polynomial_b);

    int size_polynomial_c = size_polynomial_a * size_polynomial_b;
    int array_c[size_polynomial_c] = {};

    Poly_multiply (array_a, array_b, size_polynomial_a, size_polynomial_b, array_c);

    printf ("ANS\n");
    for (int id = 0; id < size_polynomial_c; id++)
        printf ("%d ", array_c[id]);
    printf ("\n");

    return EXIT_SUCCESS;
}