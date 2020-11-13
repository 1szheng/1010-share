/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: Kendall
 *
 * Read in a sequence of numbers and find its kendall tau 
 * distance.
 *
 * @file: kendall.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"
#include <stdbool.h>

// takes in a value, a list and the size of the list
// returns the position of the value in the list, else return -1, which should not happen
// would replace with a break ver. or equiv if allowed
long find_pos(long value, const long list[], long size)
{
    for (long i = 0; i < size; i += 1)
    {
        if (list[i] == value)
        {
            return i;
        }
    }
    return -1;
}

// takes in two values of numbers, a list and its size
// returns true if first_ele comes before second_ele in the given list
bool find_pair_diff(long first_ele, long second_ele, const long list[], long size)
{
    long second_pos_list = find_pos(second_ele, list, size);  // variable to store position of second number on the list

    // iterate starting from position of the second number
    for (long i = second_pos_list; i < size; i += 1)
    {
        if (list[i] == first_ele)
        {
            return false;
        }
    }
    return true;
}

// takes in values of n and a list of its permutation of integers (1..n)
// prints out the normalized Kendall tau distance
void kendall(long n, const long list[])
{
    double diff_counter = 0;        // variable to store the number of differences found
    double normalized = 0;          // variable to store the normalized kendall tau distance
    long num_of_pairs = 0;          // variable to store the number of pairs

    // iterate from 1 to n-1
    for (long i = 0; i < (n - 1); i += 1)
    {
        // iterate through the pairs in n
        for (long pair_i = i + 1; pair_i < n; pair_i += 1)
        {
            if (!find_pair_diff(i+1, pair_i+1, list, n))
            {
                diff_counter += 1;
            }
            num_of_pairs += 1;
        }
    }

    normalized = diff_counter/num_of_pairs;
    cs1010_println_double(normalized);
}

int main()
{
    long n = cs1010_read_long();    // stores the input for n
    if (n > 1)
    {
        long *values = cs1010_read_long_array(n); // stores input for the permutated array
        if (values != NULL)
        {
            kendall(n, values);

            free(values);
        }
    }

    return 0;
}
