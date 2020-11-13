/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: CountingSort
 *
 * Read in a series of numbers between 0 and 10000 
 * and sort them using counting sort.
 *
 * @file: countingsort.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"

#define K_PLUS_ONE 10001

// takes in the number of integers (n) and a list containing n integers
// prints the sorted list 
void countingsort(long n, long *list)
{
    long counter_array[K_PLUS_ONE] = {0}; // tracks the number of appearances of each integer

    // populates counter_array with count of each integer
    for (long i = 0; i < n; i += 1)  
    {
        counter_array[*(list + i)] += 1;
    }

    long out_counter = 0;           // stores the counter to update list[] with sorted integers

    // prints the integer, its number of appearances and sort list
    // repopulates list with the sorted integers, original list is no longer required
    for (long k_counter = 0; (out_counter < n) && (k_counter < K_PLUS_ONE); k_counter += 1)
    {
        if (counter_array[k_counter] != 0)
        {
            cs1010_print_long(k_counter);       // k_counter is equivalent to the value of the integer
            cs1010_print_string(" ");
            cs1010_println_long(counter_array[k_counter]);

            // repopulate list with sorted integers
            for (long k_iterator = 0; k_iterator < counter_array[k_counter]; k_iterator += 1)
            {
                *(list + out_counter) = k_counter;
                out_counter += 1;
            }
        }
    }

    // prints out the sorted list
    for (long out = 0; out < n; out += 1)
    {
        cs1010_println_long(*(list + out));
    }
}

int main()
{
    long n = cs1010_read_long();    // stores the input for n
    if (n > 0)
    {
        long *values = cs1010_read_long_array(n); // stores input for unsorted array
        if (values != NULL)
        {
            countingsort(n, values);

            free(values);
        }
    }
    return 0;
}
