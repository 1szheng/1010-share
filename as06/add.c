/**
 * CS1010 Semester 1 AY20/21
 * Assignment 6: Add
 *
 * This file contains an implementation of addition that is able to add two
 * arbitraily large non-negative numbers. This implementation represents the
 * numbers as an arbitrarily long string consisting of characters (of type
 * `char`) `0` to `9`.
 *
 * @file: add.c
 * @author: Wan Si Zheng (Group D05)
 */

#include <string.h>
#include "cs1010.h"

#define CHAR_ZERO '0'
#define assert(expr)  ((void) (0));

/**
 * Adds the remaining char numbers in num_two into the results, after
 * summing with 'extra'.
 *
 * @pre results A non-NULL array of size (len_two + 1)
 * @pre num_two A string of chars from '0' to '9' and not NULL
 * @pre len_one > 0 && len_one <= len_two
 * @pre len_two > 0 && len_two >= len_one
 * @pre extra >= 0 && extra <= 9
 *
 * @param[out] results An array to store the result of the addition
 * @param[in] num_two A number represented by a string of chars 
 * @param[in] len_one Size of num_one, the index before the new starting index
 * @param[in] len_two Size of num_two
 * @param[in] extra The quotient of the previous summed digits divided by 10
 */
void solve_remaining(char * results, const char * num_two, long len_one, long len_two, long extra)
{
    for (long i = len_one + 1; i <= len_two; i += 1)
    {
        assert(i > len_one && i <= len_two);

        long digit = num_two[len_two - i] - CHAR_ZERO;

        long sum = digit + extra;
        extra = sum/10;

        results[(len_two + 1) - i] = (sum % 10) + CHAR_ZERO;
    }
    results[0] = (char)(extra + CHAR_ZERO);
}

/**
 * Computes the sum of two non-negative numbers which can be arbitraily large.
 *
 * @pre num_one A string of chars from '0' to '9' and not NULL
 * @pre num_two A string of chars from '0' to '9' and not NULL
 * @pre len_one > 0 && len_one <= len_two
 * @pre len_two > 0 && len_two >= len_one
 * @pre results An empty non-NULL array of size (len_two + 1)
 *
 * @param[in] num_one A number represented by a string of chars
 * @param[in] num_two A number represented by a string of chars 
 * @param[in] len_one Size of num_one
 * @param[in] len_two Size of num_two
 * @param[out] results An array to store the result of the addition
 */
void big_add(const char * num_one, const char * num_two, long len_one, long len_two, char * results)
{
    long extra = 0; // the quotient of sum divided by 10

    // iteratively add from the back, up to len_one
    for (long i = 1; (i <= len_one) && (i <= len_two); i += 1)
    {
        assert(i >= 1 && i <= len_one);
        assert(i >= 1 && i <= len_two);

        long digit_one = num_one[len_one - i] - CHAR_ZERO;
        long digit_two = num_two[len_two - i] - CHAR_ZERO;

        long sum = digit_one + digit_two + extra;
        extra = sum/10;

        // length of results is len_two + 1
        results[(len_two + 1) - i] = (sum % 10) + CHAR_ZERO;
    }

    if (len_one != len_two)
    {
        solve_remaining(results, num_two, len_one, len_two, extra);
    }
    else
    {
        results[0] = (char)(extra + CHAR_ZERO);
    }

    // check if first char is not '0'
    if (results[0] != CHAR_ZERO)
    {
        cs1010_println_string(results);
    }
    else
    {
        results += 1;
        cs1010_println_string(results);
    }
}

int main()
{
    char * num_one = cs1010_read_word();
    if (num_one == NULL)
    {
        cs1010_println_string("num_one allocation error");
        return 1;
    }

    char * num_two = cs1010_read_word();
    if (num_two == NULL)
    {
        cs1010_println_string("num_two allocation error");
        free(num_one);
        num_one = NULL;
        return 1;
    }

    long len_one = (long)strlen(num_one);
    long len_two = (long)strlen(num_two);

    char * results;

    if (len_two > len_one)
    {
        results = malloc((size_t)(len_two + 1) * sizeof(char));
        if (results == NULL)
        {
            cs1010_println_string("results allocation error");
            free(num_one);
            free(num_two);

            num_one = NULL;
            num_two = NULL;
            return 1;
        }

        big_add(num_one, num_two, len_one, len_two, results);
    }
    else
    {
        results = malloc((size_t)(len_one + 1) * sizeof(char));
        if (results == NULL)
        {
            cs1010_println_string("results allocation error");
            free(num_one);
            free(num_two);

            num_one = NULL;
            num_two = NULL;
            return 1;
        }

        big_add(num_two, num_one, len_two, len_one, results);
    }

    // clean up
    free(num_one);
    num_one = NULL;

    free(num_two);
    num_two = NULL;

    free(results);
    results = NULL;

    return 0;
}
