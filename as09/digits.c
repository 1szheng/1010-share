/**
 * CS1010 Semester 1 AY20/21
 * Assignment 9: Digits
 *
 * This file contains an implementation of the k-nearest neighbor algorithmn
 * for pattern recognition. The patterns here are integers from 0 to 9 where
 * handwritten digits are transformed into the form of images as a 2D array
 * containing `.` for white and `#` for black where the background is white.
 * This file will be passed a set of training data followed by a set of testing
 * data formatted in the same manner and uses the k-nearest neighbor algorithmn
 * to attempt to recognise the testing data provided as the correct digits. The
 * distance used for this is the number of differences in cells between the two
 * comapared images. As the distance is required to be close, in this case, it
 * the difference is below 285, and K is 5.
 * 
 *
 * @file: digits.c
 * @author: Wan Si Zheng (Group D05)
 */

#include "cs1010.h"
#include <stdbool.h>

#define LENGTH 28
#define K 5
#define MAX_DIFF 784
#define FAR 284

typedef struct digit {
    long number;
    char **pic;
} digit;

typedef struct neighbor {
    long number;
    long distance;
} neighbor;

/**
 * Attempts to insert the number-distance pair into the k-nearest neighbors.
 * The insertion will be performed in a pseudo-sorted manner where it is
 * sorted by distance but not fully on numbers. When inserting pairs which
 * has distance corresponding to another pair in neighbors, and no larger
 * distances are available for replacement, it replaces the largest number
 * which is also larger than itself and with same distance.
 *
 * @param [in, out] neighbor    The array containing k-nearest neighbors
 * @param [in]      num         The number of the most recent training image
 * @param [in]      dist        The distance of the most recent training image
 */
void attempt_insert(neighbor *neigh, long num, long dist)
{
    if (neigh[4].distance < dist)
    {
        return;
    }

    // look for index to add to
    bool strictly_less = false;
    bool is_biggereq = true;    // stays true if dist equal and num not smaller
    long replace = 0;
    for (long i = 0; (!strictly_less) && i < K; i += 1)
    {
        // found something strictly less in distance
        if (neigh[i].distance > dist)
        {
            replace = i;
            strictly_less = true;
        }
        // handling of equal distance cases, replace largest number
        else if (neigh[i].distance == dist && neigh[i].number > num)
        {
            if (neigh[i].distance > neigh[replace].distance)
            {
                replace = i;
                is_biggereq = false;
            }
            else if (neigh[i].distance == neigh[replace].distance && \
                    neigh[i].number > neigh[replace].number)
            {
                replace = i;
                is_biggereq = false;
            }
        }
    }

    if (strictly_less)
    {
        // shift numbers accordingly
        for (long i = 4; i > replace; i -= 1)
        {
            neigh[i].number = neigh[i - 1].number;
            neigh[i].distance = neigh[i - 1].distance;
        }
        neigh[replace].number = num;
        neigh[replace].distance = dist;
    }
    else if (!is_biggereq || neigh[4].distance != dist)
    {
        neigh[replace].number = num;
        neigh[replace].distance = dist;
    }
}

/**
 * Checks if two characters are the same.
 *
 * @param [in]  a The first character for comparison
 * @param [in]  b The second character for comparison
 *
 * @return      Returns true if they are the same, false otherwise
 */
bool same_cell(char a, char b)
{
    return (a == b);
}

/**
 * Counts the number of different cells between two images. Stops counting if
 * the difference is too large and returns the largest difference instead.
 *
 * @param [in]  train   The training image to be compared
 * @param [in]  test    The testing image to be compared
 *
 * @return      The difference in cells or MAX_DIFF if difference is too large
 */
long count_diff(char **train, char **test)
{
    long count = 0;
    for (long i = 0; i < LENGTH; i += 1)
    {
        for (long j = 0; j < LENGTH; j += 1)
        {
            if (!same_cell(train[i][j], test[i][j]))
            {
                count += 1;
                if (count > FAR)
                {
                    return MAX_DIFF;
                }
            }
        }
    }
    return count;
}

/**
 * Initializes a struct neighbor array of size 5. Sets its contents to MAX_DIFF
 * to accomodate sorting and insertion later.
 *
 * @return      Returns the memory address to the struct neighbor array or NULL
 *              in the event of an allocation error.
 */
neighbor *init_neighbor()
{
    neighbor *mem = malloc((size_t)K * sizeof(neighbor));
    if (mem == NULL)
    {
        return NULL;
    }
    for (long i = 0; i < K; i += 1)
    {
        mem[i].number = MAX_DIFF;
        mem[i].distance = MAX_DIFF;
    }
    return mem;
}

/**
 * The insertion algorithmn used by insertion sort, to swap/insert the
 * contents of the current index being pointed to into the appropriate index.
 *
 * @param [in, out] neigh   The array containing the k-nearest neighbors
 * @param [in]      curr    The current index to be sorted
 */
void insert(neighbor *neigh, long curr)
{
    long i = curr - 1;
    neighbor temp = neigh[curr];

    while (i >= 0 && ( neigh[i].distance > temp.distance || \
                (neigh[i].distance == temp.distance && neigh[i].number > \
                 temp.number) ))
    {
        neigh[i + 1].number = neigh[i].number;
        neigh[i + 1].distance = neigh[i].distance;
        i -= 1;
    }
    neigh[i + 1].number = temp.number;
    neigh[i + 1].distance = temp.distance;
}

/**
 * The insertion sort algorithmn to sort the k-nearest neighbors.
 *
 * @param [in, out] neigh   The array containing the k-nearest neighbors
 */
void insert_sort(neighbor *neigh)
{
    for (long curr = 1; curr < K; curr += 1)
    {
        insert(neigh, curr);
    }
}

/**
 * Checks the neighbor array for the smallest and most reoccuring digit such
 * that it is the digit recognised from the testing image.
 *
 * @param [in, out] neigh   The array containing the k-nearest neighbors
 *
 * @return          A integer from [0 - 9] that is the smallest and appeared
 *                  most number of times within the neighbor array.
 */
long find_closest_digit(neighbor *neigh)
{
    long numbers[10] = {0};
    long max = 0;
    for (long i = 0; i < K; i += 1)
    {
        numbers[neigh[i].number] += 1;
        if (numbers[neigh[i].number] > max)
        {
            max = numbers[neigh[i].number];
        }
    }
    insert_sort(neigh);

    bool found = false;
    for (long i = 0; (!found) && i < K; i += 1)
    {
        if (numbers[neigh[i].number] == max)
        {
            max = neigh[i].number;
            found = true;
        }
    }
    return max;
}

/**
 * Freeing of the arrays within the struct array and the struct array itself.
 *
 * @param [in, out] arr     The struct digit array to be free-ed
 * @param [in]      n       The number of elements in the array
 */
void free_arr_of_struct(digit* arr, long n)
{
    for (long i = 0; i < n; i += 1)
    {
        for (long j = 0; j < LENGTH; j += 1)
        {
            free(arr[i].pic[j]);
        }
        free(arr[i].pic);
    }
    free(arr);
}

/**
 * To recognise the given testing image as a digit based on the training images
 * provided and the k-nearest neighbors. Prints the digit of the original image
 * and what it was recognised as to the standard output.
 *
 * @pre train       is not NULL
 * @pre testing     is not NULL
 *                              
 * @param [in, out] train   The struct digit training data array
 * @param [in]      n       The number of images in train
 * @param [in, out] testing Array containing the test image to be recognised
 * @param [in]      num     The number the test image is supposed to be
 *
 * @return          Returns 1 if test image recognised accurately, 0 otherwise
 *                  and -1 if memory allocation error occurs.
 */
long recognise_digits(digit *train, long n, char **testing, long num)
{
    neighbor *neigh = init_neighbor();
    if (neigh == NULL)
    {
        return -1;
    }

    for (long i = 0; i < n; i += 1)
    {
        long dist = count_diff(train[i].pic, testing);
        attempt_insert(neigh, train[i].number, dist);
    }
    long seen_as = find_closest_digit(neigh);//find_most_occurrence(neigh);

    cs1010_print_long(num);
    cs1010_print_string(" ");
    cs1010_println_long(seen_as);

    free(neigh);
    if (num == seen_as)
    {
        return 1;
    }
    return 0;
}

// reads n training samples and initializes an array of struct digit
/**
 * Initializes an array of struct digit by allocating memory of size n
 * and initializing the structs within by reading the number and 2D array
 * image from the standard input n times.
 *
 * @param [in]  n   The size of the struct digit array to be initialized
 *
 * @return          Returns the memory address to the struct digit array or NULL
 *                  in the event of an allocation error.
 */
digit *read_samples(long n)
{
    digit *mem = malloc((size_t)n * sizeof(digit));
    if (mem == NULL)
    {
        cs1010_println_string("memory alloc error 1.0");
        return NULL;
    }

    for (long i = 0; i < n; i += 1)
    {
        mem[i].number = cs1010_read_long();
        mem[i].pic = cs1010_read_line_array(LENGTH);
        if (mem[i].pic == NULL)
        {
            free_arr_of_struct(mem, (i - 1));
            cs1010_println_string("memory alloc error 1.1");
            return NULL;
        }
    }
    return mem;
}

int main() 
{
    long n = cs1010_read_long();
    digit *train = read_samples(n);
    if (train == NULL)
    {
        return 1;
    }

    long m = cs1010_read_long();
    digit *testing = read_samples(m);
    if (testing == NULL)
    {
        free_arr_of_struct(train, n);
        return 1;
    }

    long count = 0;
    for (long i = 0; (count != -1) && i < m; i += 1)
    {
        count += recognise_digits(train, n, testing[i].pic, testing[i].number);
    }
    cs1010_println_double((count * 1.0)/m * 100);

    free_arr_of_struct(train, n);
    free_arr_of_struct(testing, m);
    return 0;
}
