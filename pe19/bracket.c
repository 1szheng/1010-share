/**
 * CS1010 Semester 1 AY18/19
 * Practical Exam 2: Bracket 
 *
 * @file: bracket.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"
#include <string.h>
#include <stdbool.h>

bool checker(char A, char B)
{
    if ((A == '<' && B == '>') ||\
        (A == '{' && B == '}') ||\ 
        (A == '[' && B == ']') ||\
        (A == '(' && B == ')'))
    {
        return true;
    }
    return false;
}

bool bracket(char * array, char * ministack, long start, long end, long * counter)
{
    if (array[start] == ')' || array[start] == '}' || \
            array[start] == '>' || array[start] == ']')
    {
        if (start == 0)
        {
            return false;
        }
        if (!checker(ministack[*counter - 1], array[start]))
        {
            return false;
        }
        *counter -= 1;
        ministack[*counter] = ' ';
    }
    else
    {
        ministack[*counter] = array[start];
        *counter += 1;
    }

    if (start != end)
    {
        return bracket(array, ministack, start + 1, end, counter);
    }

    if (*counter == 0)
    {
        return true;
    }
    return false;
}


int main()
{
    char *array = cs1010_read_word();
    long len = (long)strlen(array);

    char *ministack = malloc((size_t)len * sizeof(char));
    if (ministack == NULL)
    {
        return 1;
    }
    long counter = 0;
    if (bracket(array, ministack, 0, len - 1, &counter))
    {
        cs1010_println_string("yes");
    }
    else
    {
        cs1010_println_string("no");
    }

}
