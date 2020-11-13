/**
 * CS1010 Semester 1 AY20/21
 * Assignment 7: Sort
 *
 * This file contains an implementation to sort an almost sorted list.
 * The list contains n numbers of unique ids, and the definition of
 * almost sorted is given by the first k ids being in ascending order
 * and the remaining n - k being in descending order. The value of k
 * is not given. The sorted list will be printed to standard output.
 *
 * @file: sort.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"

/**
 * Finds and returns the index of the minimum value.
 *
 * @pre values assumed to be not null
 * @pre front >= 0 && < n
 * @pre back >= 1 && < n
 *
 * @param[in] values The almost sorted list containing unique ids
 * @param[in] front The index counting the front sorted area
 * @param[in] back The index counting the back sorted area
 *
 * @return Returns the index of the minimum value
 */
long min_index(const long * values, long front, long back)
{
    if (values[front] < values[back])
    {
        return front;
    }
    return back;
}

/**
 * Sorts the almost sorted list and prints the results to standard output.
 *
 * @pre values assumed to be not null
 * @pre n >= 1
 *
 * @param[in] values The almost sorted list containing unique ids
 * @param[in] n The number of ids that exists in the list
 */
void sort(const long * values, long n)
{
    long front = 0;
    long back = 1;
    long curr;

    while ((front + back - 1) != n)
    {
        curr = min_index(values, front, n - back);

        cs1010_print_long(values[curr]);
        cs1010_print_string(" ");

        if (curr == front)
        {
            front += 1;
        }
        else
        {
            back += 1;
        }
    }
    cs1010_println_string("");
}

int main()
{
    long n = cs1010_read_long();

    if (n >= 1)
    {
        long *values = cs1010_read_long_array(n);
        if (values == NULL)
        {
            cs1010_println_string("memory allocation error");
            return -1;
        }

        sort(values, n);

        free(values);
        values = NULL;
    }
    return 0;
}
