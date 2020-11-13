/**
 * CS1010 Semester 1 AY18/19
 * Assignment 4: SelectionSort
 *
 * This file contains an implementation of the selection sort algorithm,
 * whereby the size of the array to be sorted and the array itself will be
 * read from the standard input, then the sorting process in terms of the
 * state of the array will be printed to the standard output.
 * The sorting is performed by through a series of value swapping. First,
 * the index of the largest integer will be located, and a swap will occur
 * if it is not in the last index i.e. (n - 1). Subsequently, the next largest
 * integer will be located and swapped to the second last index. This repeats
 * itself until the array has been sorted in ascending order.
 *
 * @file: selectionsort.c
 * @author: Wan Si Zheng (Group D05)
 */

#include "cs1010.h"
#include <stdbool.h>

/**
 * Takes in an array with n number of integers, prints the integers within
 * the list to the standard output.
 *
 * @pre list is not empty nor NULL
 * @pre n is > 1
 *
 * @param[in] list The (long) array to be read
 * @param[in] n The number of integers to be read
 */
void print_array(const long list[], long n)
{
    for (long i = 0; i < n; i += 1)
    {
        cs1010_print_long(list[i]);
        cs1010_print_string(" ");
    }
    cs1010_println_string("");
}

/**
 * Takes in an array with n number of integers.
 * Perform selection sort on the array by looping through the array
 * (n - 1) times. Print the state of the array at the end of each sorting
 * iteration to the standard output. Sorting is performed by iteratively
 * finding and swapping the largest, or the subsequent largest, integers
 * to its appropriate index i.e. from (n - 1), (n - 2) to 0. Searching and
 * swapping of integers no longer occurs once it is found that the array is
 * already sorted such that for every integer, the integer in the next index
 * is larger than itself. The array is then printed for the remaining of the
 * (n - 1) times to emulate the remaining 'sorting'.
 *
 * @pre list is not empty nor NULL
 * @pre list contains only unique integers
 * @pre n is > 1
 *
 * @param[in, out] list The (long) array to be selection sorted
 * @param[in] n The number of integers in the array
 */
void selection_sort(long list[], long n)
{
    long max_index;         // stores the index of the max value found
    long temp;              // stores temporary values for swapping
    bool sorted = false;    // state of total sorted-ness

    // loops (n - 1) times
    for (long i = (n - 1); i > 0; i -= 1)
    {

        max_index = i;
        bool smaller_than_next = true; // stays true if array is sorted

        if (!sorted)
        {
            // iterates from index 0 to (i - 1)
            // to find new max_index, if available
            for (long iterator = 0; iterator < i; iterator += 1)
            {
                if (list[iterator] > list[max_index])
                {
                    max_index = iterator;
                }
                // checks if array is already sorted i.e. 1 < 2 < 3
                if (list[iterator] > list[iterator + 1])
                {
                    smaller_than_next = false;
                }
            }

            // array is sorted, else check for swap
            if (smaller_than_next)
            {
                sorted = true;
            }
            else
            {
                // the swapping of values if max_index has been modified
                if (max_index != i)
                {
                    temp = list[i];
                    list[i] = list[max_index];
                    list[max_index] = temp;
                }
            }
        }
        print_array(list, n);
    }
}

/**
 * Reads the number of elements of the array and the array
 * to be sorted from the standard input. 
 
 * Given that there is no memory allocation error and number
 * of elements is at least 2, pass the two as arguments into
 * selection_sort to be sort the array. Thereafter, free the
 * memory allocated for the array.
 *
 * @return Returns 1 if there is either a memory allocation error, or
 * number of elements is less than 2 as there is nothing to sort.
 * @return Returns 0 if no handled issues occur.
 */
int main() 
{
    long num_of_ele = cs1010_read_long();
    long *values = cs1010_read_long_array(num_of_ele);

    if (values == NULL || num_of_ele < 2)
    {
        return 1;
    }

    selection_sort(values, num_of_ele);

    free(values);
    return 0;
}
