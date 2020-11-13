/**
 * CS1010 Semester 1 AY20/21
 * Assignment 8: Walk
 *
 * This file contains an implementation to find the number of possible
 * paths to a destination. Consider the cartesian plane, this implementation
 * finds the number of possible paths from (0, 0) to a coordinate given by x
 * and y integers. The path to the destination may only be created by pathing
 * northwards towards y or eastwards towards x.
 *
 * @file: walk.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"

/**
 * Calculates the number of possible paths to the destination (x, y) by
 * utilising a nested loop. An array of size (x + 1) is created to hold 
 * the number of possible paths to reach a given y coordinate at the x
 * values given from 0 to x. The number of possible paths to reach any
 * coordinate on y = 0 or x = 0 is 1, and the number of possible paths
 * to any (x, y) is given by summing the number of paths from (x - 1, y)
 * and (x, y - 1). After each iteration of the outer loop from y = 1, the
 * array will be updated to contain the possible paths to reach the x value
 * coordinates on the iterated y value.
 *
 * @pre x >= 0
 * @pre y >= 0
 *
 * @param[in] x The destination coordinate by x
 * @param[in] y The destination coordinate by y
 */
void walk(long x, long y)
{
    long *array = malloc((size_t)(x + 1) * sizeof(long));
    if (array == NULL)
    {
        return;
    }

    // initialise each element in 0th row to 1 as it takes 1 step
    for (long i = 0; i <= x; i++)
    {
        array[i] = 1;
    }

    // iterate rows [1..y]
    for (long i = 1; i <= y; i++)
    {
        // iterate col [1..x]
        for (long j = 1; j <= x; j++)
        {
            array[j] += array[j-1];
        }
    }
    cs1010_println_long(array[x]);
    free(array);
    array = NULL;
}

int main() 
{
    long x = cs1010_read_long();
    long y = cs1010_read_long();

    walk(x,y);

    return 0;
}
