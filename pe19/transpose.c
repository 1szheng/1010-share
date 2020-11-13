/**
 * CS1010 Semester 1 AY18/19
 * Practical Exam 2: Transpose 
 *
 * @file: transpose.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"
#include <stdbool.h>

void transpose_matrix(double **m1, double **m2, long nrows, long ncols)
{
    for (long i = 0; i < nrows; i += 1)
    {
        for (long j = 0; j < ncols; j += 1)
        {
            m2[j][i] = m1[i][j];
        }
    }

    for (long i = 0; i < ncols; i += 1)
    {
        for (long j = 0; j < nrows; j += 1)
        {
            cs1010_print_double(m2[i][j]);
            cs1010_print_string(" ");
        }
        cs1010_println_string("");
    }
}

void free_2d_array(void **a, size_t m) {
    for (size_t i = 0; i < m; i += 1) {
        free(a[i]);
    }
    free(a);
}

int main()
{
    long m = cs1010_read_long();
    long n = cs1010_read_long();

    double **m1 = malloc((size_t)m * sizeof(double *));
    if (m1 == NULL)
    {
        return 1;
    }

    for (long i = 0; i < m; i += 1)
    {
        m1[i] = cs1010_read_double_array(n);
        if (m1[i] == NULL)
        {
            for (long j = 0; j < i; j += 1)
            {
                free(m1[i]);
            }
            free(m1);
            return 1;
        }
    }

    double **m2 = malloc((size_t)n * sizeof(double *));
    if (m2 == NULL)
    {
        return 1;
    }
    for (long i = 0; i < n; i += 1)
    {
        m2[i] = malloc((size_t)m * sizeof(double));
        if (m2[i] == NULL)
        {
            for (long j = 0; j < i; j += 1)
            {
                free(m2[j]);
            }
            free_2d_array((void **)m1, (size_t)m);
            free(m2);
            return 1;
        }
    }

    transpose_matrix(m1, m2, m, n);

    for (long i = 0; i < m; i += 1)
    {
        free(m1[i]);
    }
    for (long j = 0; j < n; j += 1)
    {
        free(m2[j]);
    }
    free(m1);
    free(m2);

    // clean up
    //free_2d_array((void **)m1, (size_t)m);
    //free_2d_array((void **)m2, (size_t)n);
}
