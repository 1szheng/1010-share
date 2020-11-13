/**
 * CS1010 Semester 1 AY20/21
 * Assignment 6: Permutation
 * 
 * Given two strings of lowercase letters 'a' to 'z', with 
 * first string no longer than the second. This program 
 * checks if the 1st string is a permutation of a substring 
 * of the 2nd one.
 *
 * @file: permutation.c
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
 * Given two arrays containing the frequency of the letters in the 1st 
 * string and in the substring of second, check if the frequencies are
 * the same such that the 1st string is a permutation of that substring.
 *
 * @pre count_S1 Assumed to be not NULL, length == number of alphabets
 * @pre window_S2 Assumed to be not NULL, length == number of alphabets
 * @pre len_S1 > 0
 *
 * @param[in] count_S1 The frequency of letters of the 1st string
 * @param[in] window_S2 The frequency of the letters of the substring
 * @param[in] len_S1 The length of the 1st string
 *
 * @return Return true if the 1st string is a permutation of the substring,
 *  otherwise return false.
 */
bool isPermute(const long count_S1[], const long window_S2[], long len_S1)
{
    long count = 0;
    for (long i = 0; (count < len_S1) && (i < ALPHABETS_LEN); i += 1)
    {
        assert(i >= 0 && i < ALPHABETS_LEN);
        assert(count < len_S1);

        if (count_S1[i] != window_S2[i])
        {
            return false;
        }
        count += count_S1[i];
    }
    return true;
}

/**
 * Given two strings of lowercase letters 'a' to 'z', with first string 
 * no longer than the second, checks if the 1st string is a permutation 
 * of a substring of the 2nd one. Prints the results to standard output.
 *
 * @pre S1 Assumed to be not NULL, length at most same as S2
 * @pre S2 Assumed to be not NULL, length at least same as S1
 *
 * @param[in] S1 A string of lowercase letters
 * @param[in] S2 A string of lowercase letters
 */
void permutation(const char * S1, const char * S2)
{
    // counts number of times each letter appears in S1
    long count_S1[ALPHABETS_LEN] = {0};

    // counts number of times each letter appears in a substring of S2
    long window_S2[ALPHABETS_LEN] = {0};

    long len_S1 = (long)strlen(S1) - 1;
    long len_S2 = (long)strlen(S2) - 1;

    // iterate for all index in S1
    for (long i = 0; i < len_S1; i += 1)
    {
        assert(i >= 0 && i < len_S1);

        long char1 = (S1[i] - FROM_CHAR) - TO_ALPHABET;
        long char2 = (S2[i] - FROM_CHAR) - TO_ALPHABET;

        assert(char1 < ALPHABETS_LEN && char2 < ALPHABETS_LEN);

        count_S1[char1] += 1;
        window_S2[char2] += 1;
    }

    bool result = false;

     checking for existence of permutation
    if (len_S1 != len_S2)
    {
        // iterate for rest of S2
        for (long j = len_S1; (!result) && (j < len_S2); j += 1)
        {
            result = isPermute(count_S1, window_S2, len_S1);

            // shifting window to next
            if (!result)
            {
                assert(j >= len_S1 && j < len_S2);

                long char2 = (S2[j] - FROM_CHAR) - TO_ALPHABET;
                long earliest = (S2[(j - len_S1)] - FROM_CHAR) - TO_ALPHABET;

                assert(char2 < ALPHABETS_LEN && earliest < ALPHABETS_LEN);

                window_S2[char2] += 1;      // adding current char to array
                window_S2[earliest] -= 1;   // removing earliest char
            }
        }
        // check for permutation with last letter of S2 included
        if (!result)
        {
            result = isPermute(count_S1, window_S2, len_S1);
        }
    }
    else
    {
        result = isPermute(count_S1, window_S2, len_S1);
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

    permutation(string1, string2);

    // clean up
    free(string1);
    free(string2);
    string1 = NULL;
    string2 = NULL;

    return 0;
}
