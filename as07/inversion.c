/**
 * CS1010 Semester 1 AY20/21
 * Assignment 7: Inversion
 *
 * This file contains an implementation to count the number of inversions
 * given an almost sorted list. The list contains n numbers of unique ids,
 * and the definition of sorted is given by the first k ids being in
 * ascending order and the remaining n - k being in descending order. The
 * value of k is not given. Inversion is defined as a pair of ids that is
 * out of order. A perfectly sorted list would have 0 inversions and
 * inversely sorted list would have n(n-1)/2 inversions. The almost sorted 
 * list provided will be sorted properly and the number of inversions will
 * be printed to the standard output.
 *
 * @file: inversion.c
 * @author: Wan Si Zheng (Group D05)
 */

#include <stdbool.h>
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
 * Sorts the almost sorted list, unsorted, and insert the IDs into their
 * appropriate positions in sorted, and the index of insertion into sort_idx.
 *
 * @pre unsorted assumed to be not NULL
 * @pre n >= 1
 * @pre sorted assumed to be not NULL
 * @pre sort_idx assumed to be not NULL
 *
 * @param[in] unsorted The almost sorted list containing unique IDs/scripts
 * @param[in] n The number of unique IDs/scripts
 * @param[out] sorted The properly sorted list containing unique IDs/scripts
 * @param[out] sort_idx The array containing the index of the unsorted ID in
 *      sorted e.g. sort_idx[unsorted_index] == sorted_index
 */
void sort(const long * unsorted, long n, long * sorted, long * sort_idx)
{
    long front = 0;
    long back = 1;
    long curr;
    long index = 0;

    while ((front + back - 1) != n)
    {
        curr = min_index(unsorted, front, n - back);

        sorted[index] = unsorted[curr];

        sort_idx[curr] = index;

        if (curr == front)
        {
            front += 1;
        }
        else
        {
            back += 1;
        }
        index += 1;
    }
}

/**
 * Counts the number of inversions by first iterating the list up to the peak,
 * k, then calculate the remaining inversions based on the n(n-1)/2 formula
 * where n is the number of remaining IDs. Prints the number of inversions to
 * standard output.
 *
 * @pre unsorted assumed to be not NULL
 * @pre n >= 1
 * @pre sorted assumed to be not NULL
 * @pre sort_idx assumed to be not NULL
 *
 * @param[in] unsorted The almost sorted list containing unique IDs/scripts
 * @param[in] n The number of unique IDs/scripts
 * @param[in] sorted The properly sorted list containing unique IDs/scripts
 * @param[in] sort_idx The array containing the index of the unsorted ID in
 *      sorted e.g. sort_idx[unsorted_index] == sorted_index
 */
void inversion(const long * unsorted, long n, const long * sorted, const long * sort_idx)
{
    long inverts = 0;
    long peak = 0;
    bool isPeak = false;

    // iterates for the area before the peak
    // any ID out of place has inversions amounted to its sorted index minus any
    // checked IDs before it
    for (long i = 0; (!isPeak) && i < n - 1; i += 1)
    {
        if (unsorted[i] != sorted[i])
        {
            inverts += (sort_idx[i] - i);

            // check for peak
            if (unsorted[i] > unsorted[i + 1])
            {
                peak = i;
                isPeak = true;
            }
        }
    }

    if (isPeak)
    {
        inverts += (n - peak - 1) * (n - peak - 2) / 2 ;
    }

    cs1010_println_long(inverts);
}

int main()
{
    long n = cs1010_read_long();

    if (n >= 1)
    {
        long *unsorted = cs1010_read_long_array(n);
        if (unsorted == NULL)
        {
            cs1010_println_string("unsorted allocation error");

            return -1;
        }

        long *sorted = malloc((size_t)n * sizeof(long));
        if (sorted == NULL)
        {
            cs1010_println_string("sorted allocation error");
            free(unsorted);

            return -1;
        }
        
        long *sort_idx = malloc((size_t)n * sizeof(long));
        if (sort_idx == NULL)
        {
            cs1010_println_string("sort_index allocation error");
            free(unsorted);
            free(sorted);

            return -1;
        }

        sort(unsorted, n, sorted, sort_idx);
        inversion(unsorted, n, sorted, sort_idx);

        free(sorted);
        free(unsorted);
        free(sort_idx);

        return 0;
    }
    cs1010_println_string("invalid n");
    return -2;
}
