/**
 * CS1010 Semester 1 AY20/21
 * Assignment 7: Peak
 *
 * This file contains an implementation of an algorithmn to find the peak
 * location in a linear area. The peak is defined as the location that is
 * strictly higher than its surrounding locations. The data of the linear
 * area is provided such that the elevation always remains the same or
 * increases over a distance. Once the peak has been reached, the elevation
 * either always remains the same or decreases. It is possible for the
 * elevation is always non-decreasing, non-increasing, or being a plateau
 * where there are multiple locations with the same elevation. A peak may
 * not exist, but if it does, there is exactly one peak. Print to standard
 * output the index of the peak if it exists.
 *
 * @file: peak.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"

/**
 * Checks the edge cases' neighbour for peaks.
 * If the said neighbours are not peaks, then peaks
 * do not exist.
 *
 * @pre array assumed to be not NULL
 * @pre mid is 0 or n - 1
 * @pre n >= 3
 *
 * @param[in] array Data containing location elevation
 * @param[in] mid The index of the edge case
 * @param[in] n The number of elements in the array
 *
 * @return Returns index of peak if it exists, -1 otherwise
 */
long edge_check(const long * array, long mid, long n)
{
    long peak = -1;

    if (mid == 0 && array[mid] < array[mid + 1])
    {
        peak = mid + 1;
    }
    else if (mid == n - 1 && array[mid] < array[mid - 1])
    {
        peak = mid - 1;
    }
    return peak;
}

/**
 * Searches for the peak within a given set of elevation data
 * recursively.
 *
 * @pre array assumed to be not NULL
 * @pre start >= 0 && <= n
 * @pre end >= 0 && <= n
 * @pre n >= 3
 *
 * @param[in] array Data containing location elevation
 * @param[in] start The index of the lowerbound of the array
 * @param[in] end The index of the upperbound of the array
 * @param[in] n The number of elements in the array
 *
 * @return Returns the index of peak if it exists, -1 otherwise
 */
long peak_search(const long * array, long start, long end, long n)
{
    if (start > end)
    {
        return -1; // peak not found
    }

    long mid = start + (end - start)/2;
    long peak;

    if (mid == 0 || mid == n - 1)
    {
        peak = edge_check(array, mid, n);
    }
    else if (array[mid] > array[mid - 1] && array[mid] > array[mid + 1])
    {
        peak = mid; // peak found
    }
    else if (array[mid] > array[mid - 1] && array[mid] >= array[mid + 1])
    {
        peak = peak_search(array, mid + 1, end, n); // ascend
    }
    else if (array[mid] < array[mid - 1] && array[mid] <= array[mid + 1])
    {
        peak = peak_search(array, start, mid - 1, n); // descend
    }
    else
    {
        if (array[mid] < array[mid + 1])
        {
            peak = peak_search(array, mid + 1, end, n); // ascend
        
        }
        else if (array[mid] > array[mid + 1])
        {
            peak = peak_search(array, start, mid - 1, n); // descend
        }
        else
        {
            // plateau area
            long left = peak_search(array, mid + 1, end, n);
            long right = peak_search(array, start, mid - 1, n);

            if (left > right)
            {
                peak = left;
            }
            else if (left < right)
            {
                peak = right;
            }
            else
            {
                peak = -1;
            }
        }
    }

    return peak;
}

int main()
{
    long n = cs1010_read_long();

    if (n >= 3)
    {
        long *values = cs1010_read_long_array(n);
        if (values == NULL)
        {
            cs1010_println_string("memory allocation error");
            return -1;
        }

        long peak = peak_search(values, 0, n - 1, n);
        if (peak == -1)
        {
            cs1010_println_string("no peak");
        }
        else
        {
            cs1010_println_long(peak);
        }

        free(values);
        values = NULL;
    }
    return 0;
}
