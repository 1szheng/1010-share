/**
 * CS1010 Semester 1 AY18/19
 * Practical Exam 2: Rotate 
 *
 * @file: rotate.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"

long search(long *values, start, end, q)
{
    if (start > end)
    {
        return -1;
    }

    long mid = start + (end - start)/2;
    if (values[mid] == q)
    {
        return mid;
    }

    // q smaller than mid
    if (values[mid] > q)
    {
        // mid smaller than end
        if (values[mid] < values[end])
        {
            return search(values, start, mid - 1, q);
        }
        return search(values, 
    }

}

int main()
{
    long n = cs1010_read_long();
    long *values = cs1010_read_long_array(n);
    if (values == NULL)
    {
        return 1;
    }
    long q = cs1010_read_long();

    //

    return 0;
}
