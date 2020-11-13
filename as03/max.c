/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: Max
 *
 * Read in a sequence of numbers and recursively find
 * the maximum.
 *
 * @file: max.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"

// takes in a list, starting position and ending position
// recursively find and return the largest number between the two positions
long max(const long list[], long start, long end)
{
    if (start == end)
    {
        return list[start];
    }

    long mid = (start + end)/2;         // variable to store the position of the middle number
    long left = max(list, start, mid);  // variable to store the max value of the left side
    long right = max(list, mid+1, end); // variable to store the max value of the right side

    if (left > right)
    {
        return left;
    }
    return right;
}

int main()
{
    long n = cs1010_read_long();    // stores the input for n
    if (n > 0)
    {
        long *values = cs1010_read_long_array(n); // stores input for the list of integers L
        if (values != NULL)
        {
            cs1010_println_long(max(values, 0, n-1));   //n-1 due to passing it in as a position

            free(values);
        }
    }
}
