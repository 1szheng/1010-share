/**
 * CS1010 Semester 1 AY20/21
 * Exercise 5: Fill
 *
 * TODO(by student): Brief description of the purpose 
 * of this program.
 *
 * @file: fill.c
 * @author: XXX (Group XXX)
 */

#include "cs1010.h"
#include <string.h>
#include <stdbool.h>

// read and init canvas array
char **read_array(long m)
{
    char **s = malloc((size_t)m * sizeof(char *));
    if (s == NULL)
    {
        cs1010_println_string("memory allocation error");
        return NULL;
    }
    for (long i = 0; i < m; i += 1)
    {
        s[i] = cs1010_read_line();
        if (s[i] == NULL)
        {
            cs1010_println_string("memory allocation error");
            for (long j = 0; j < i; j += 1)
            {
                free(s[i]);
            }
            free(s);
            return NULL;
        }
    }
    return s;
}

// freeing of any 2d array
void free_2d(void **arr, long m)
{
    for (long i = 0; i < m; i += 1)
    {
        free(arr[i]);
    }
    free(arr);
}

// init bool 2d array
bool **init_2d(long m, long n)
{
    bool **s = malloc((size_t)m * sizeof(long *));
    if (s == NULL)
    {
        cs1010_println_string("memory allocation error 2");
        return NULL;
    }
    for (long i = 0; i < m; i += 1)
    {
        s[i] = malloc((size_t)n * sizeof(bool *));
        if (s[i] == NULL)
        {
            cs1010_println_string("memory allocation error 2");
            for (long j = 0; j < i; j += 1)
            {
                free(s[i]);
            }
            free(s);
            return NULL;
        }
    }
    return s;
}

bool spread(char **canvas, bool **visited, long m, long n, long row, long col, char og, char new)
{
    if (row >= m || row < 0 || col >= n || col < 0)
    {
        return false;
    }

    visited[row][col] = true;

    if (canvas[row][col] != og)
    {
        return false; // not connected
    }
    canvas[row][col] = new;

    long direction[4][2] = {{1,0}, {-1,0}, {0, 1}, {0, -1}};

    for (long i = 0; i < 4; i += 1)
    {
        long next_row = direction[i][0];
        long next_col = direction[i][1];

        long n_row = row + next_row;
        long n_col = col + next_col;

        // within scope
        if (n_row < m && n_row >= 0 && n_col < n && n_col >= 0)
        {
            // not visited
            if (!visited[row + next_row][col + next_col])
            {
                spread(canvas, visited, m, n, (row + next_row), (col + next_col), og, new);
            }
        }
    }
    return false;
}

// print canvas
void printa(char **array, long m)
{
    for (long i = 0; i < m; i += 1)
    {
        cs1010_print_string(array[i]);
    }
}

// reset tracker to 0
void zero(bool **a, long m, long n)
{
    for (long i = 0; i < m; i += 1)
    {
        for (long j = 0; j < n; j += 1)
        {
            a[i][j] = false;
        }
    }
}

int main() {

    long m = cs1010_read_long();
    long n = cs1010_read_long();
    char **array = read_array(m);
    if (array == NULL)
    {
        return 1;
    }

    long q = cs1010_read_long();

    bool **track = init_2d(m, n);
    if (track == NULL)
    {
        free_2d((void **)array, m);
        return 1;
    }

    for (long i = 0; i < q; i += 1)
    {
        long row = cs1010_read_long();
        long col = cs1010_read_long();
        char* new = cs1010_read_word();

        char og = array[row][col];

        zero(track, m, n);
        spread(array, track, m, n, row, col, og, new[0]);
        free(new);
    }
    printa(array, m);

    // clean up
    free_2d((void **)array, m);
    free_2d((void **)track, m);
}
