#include <cmath>
#include <complex.h>

#include "Fast_fourier_transform.h"

#include "../src/Generals_func/generals.h"
#include "../src/log_info/log_errors.h"


static void Complex_arr (double _Complex* dst_array, int *src_array, 
                                          const int old_size, const int new_size);

static void Get_polynom(const char *number, int *polynom);

//================================================================================

void Poly_multiply (int *array_a, int *array_b, const int size_a, const int size_b, int *result) 
{
    assert (array_a != nullptr && "array_a is nullptr");
    assert (array_b != nullptr && "array_b is nullptr");
    assert (result  != nullptr && "result is nullptr");

    int max_size = MAX (size_a, size_b);

    int size = 1;
    while (size < max_size)
        size *= 2;
    size *= 2;
    
    double _Complex new_array_a [size] = {};
    Complex_arr (new_array_a, array_a, size, size_a);
    FFT (new_array_a, size);

    double _Complex new_array_b [size] = {};
    Complex_arr (new_array_b, array_b, size, size_b);
    FFT (new_array_b, size);

    
    double _Complex array_result[size] = {};

    for (int i = 0; i < size; i++)
        array_result[i] = new_array_a[i] * new_array_b[i];

    FFT (array_result, size, true);

    for (int id = 0; id < size; id++)
        result[id] = (int) (creal(array_result[id]) + 0.5);

    return;
}

//================================================================================

void Numbers_multiply (const char* num1, const char* num2) 
{
    assert (num1 != nullptr && "num1 is nullptr");
    assert (num2 != nullptr && "num2 is nullptr");

    int len_num1 = strlen (num1);
    int array_num1[len_num1] = {};
    Get_polynom (num1, array_num1);

    int len_num2 = strlen (num2);
    int array_num2[len_num2] = {};
    Get_polynom (num2, array_num2);

    int size = len_num1 * len_num2;
    int result[size] = {};

    Poly_multiply (array_num1, array_num2, len_num1, len_num2, result);    

    int carry = 0;
	for (int id = 0; id < len_num1 * len_num2; id++) {
		result[id] += carry;
		carry = result[id] / 10;
		result[id] %= 10;
	}

    int id = size - 1;
    while (id >= 0 && result[id] == 0)
        id--;

    while (id >= 0)
    {
        printf ("%d", result[id]);
        id--;
    }
    
    printf ("\n");

    return;
}

//================================================================================

static void Get_polynom(const char *number, int *polynom)
{  
    assert(number != nullptr && "num is nullptr");
    assert(polynom != nullptr && "polynom is nullptr");


    int id = 0;
    while (*(number + id) != '\0' && *(number + id) != '\n')
    {
        polynom[id] = (*(number + id) - '0');
        id++;
    }

    int len = id;
    for (id = 0; id < len / 2; id++)
    {
        int digit = polynom[id];
        polynom[id] = polynom[len - id -1];
        polynom[len - id -1] = digit;
    }

    
    return;
}

//================================================================================

void FFT (double _Complex *array, const int size, bool inverse)
{
    assert (array != nullptr && "assert is nullptr");

    if (size == 1)
        return;

    int _size = size / 2;
    
    double _Complex even_polynomial[_size] = {};
    double _Complex odd_polynomial[_size]  = {};
    

    for (int id = 0; id < size; id++)
    {
        if (id % 2 == 0)
            even_polynomial[id / 2] = array[id];
        else
            odd_polynomial[id / 2]  = array[id];
    }

    FFT (even_polynomial, _size, inverse);
    FFT (odd_polynomial, _size, inverse);

    double angle = 2*M_PI/size * (inverse ? -1 : 1);
    double _Complex root = cos(angle) + sin(angle) * I;
    double _Complex droot  = 1;

    for (int id = 0; id < size; id++)
    {
        array[id] = even_polynomial[id % _size] + droot * odd_polynomial[id % _size];
        if (inverse) array[id] /= 2;

        droot *= root;
    }

    return;
}

//================================================================================

static void Complex_arr (double _Complex* dst_array, int *src_array, 
                                    const int new_size, const int old_size)
{
    assert (dst_array != nullptr && "dst_array is nullptr");
    assert (src_array != nullptr && "src_array is nullptr");


    for (int id  = 0; id < new_size; id++)
    {
        if (id < old_size)
            dst_array[id] = (double _Complex) src_array[id];
        else
            dst_array[id] = 0;
    }

    return;
}

//================================================================================

void Read_numerical_array (FILE* fpin, int array[], const int size)
{
    assert (fpin != nullptr && "fpin is nullptr");

    if (size <= 0)
    {
        Err_report ("Invalid array size = %d\n", size);
        return;
    }

    for (int id = 0; id < size; id++)
    {
        int scan_result = fscanf (fpin, "%d", &array[id]);

        if (scan_result != 1)
        {
            Err_report ("Not a number was entered\n");
            return;
        }
    }

    return;
}

//================================================================================