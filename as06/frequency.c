/**
 * CS1010 Semester 1 AY20/21
 * Assignment 6: Frequency
 * 
 * Given 2 equal length string of small letter 'a' 
 * to 'z', this program checks if both have the
 * same set of alphabets appearing the same number
 * of time.
 *
 * @file: frequency.c
 * @author: Wan Si Zheng (Group D05)
 */

#include <stdbool.h>
#include <string.h>
#include "cs1010.h"

#define TO_ALPHABET 49
#define FROM_CHAR '0'
#define ALPHABETS_LEN 26
#define assert(expr)  ((void) (0));

/**
 * Prints "YES" or "NO" to standard output depending on result
 * of the string alphabet comparison.
 *
 * @pre result Assumed to be initialised to true or false
 *
 * @param[in] result The boolean representation of the results of the
 *  string comparison.
 */
void answer(bool result)
{
    if (result)
    {
        cs1010_println_string("YES");
    }
    else
    {
        cs1010_println_string("NO");
    }
}

/**
 * Given 2 equal length strings of small letters from 'a' to 'z',
 * check if both strings have the same set of alphabets appearing
 * the same number of times. Prints the result to standard output.
 *
 * @pre S1 Assumed to be not NULL, length same as S2
 * @pre S2 Assumed to be not NULL, length same as S1
 *
 * @param[in] S1 A string of lowercase letters
 * @param[in] S2 A string of lowercase letters
 */
void frequency(const char * S1, const char * S2)
{
    // counts number of times each letter appears in S1
    long count_S1[ALPHABETS_LEN] = {0};

    // counts number of times each letter appears in S2
    long count_S2[ALPHABETS_LEN] = {0};

    long len = (long)strlen(S1) - 1;

    // iterate through S1 and S2
    for (long i = 0; i < len; i += 1)
    {
        assert(i >= 0 && i < len);

        long char1 = (S1[i] - FROM_CHAR) - TO_ALPHABET;
        long char2 = (S2[i] - FROM_CHAR) - TO_ALPHABET;

        assert(char1 < ALPHABETS_LEN && char2 < ALPHABETS_LEN);

        count_S1[char1] += 1;
        count_S2[char2] += 1;
    }

    bool result = true;
    long count = 0;

    // compare counts
    for (long j = 0; (result) && (count < len) && (j < ALPHABETS_LEN); j += 1)
    {
        assert(j >= 0 && j < ALPHABETS_LEN);
        assert(count < len);

        if (count_S1[j] != count_S2[j])
        {
            result = false;
        }

        count += count_S1[j];
    }

    answer(result);
}

int main()
{
    char * string1 = cs1010_read_line();
    if (string1 == NULL)
    {
        cs1010_println_string("string1 allocation error");
        return 1;
    }

    char * string2 = cs1010_read_line();
    if (string2 == NULL)
    {
        cs1010_println_string("string2 allocation error");
        free(string1);
        string1 = NULL;
        return 1;
    }

    frequency(string1, string2);

    // clean up
    free(string1);
    free(string2);
    string1 = NULL;
    string2 = NULL;

    return 0;
}
