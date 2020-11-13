/**
 * CS1010 Semester 1 AY18/19
 * Practical Exam 2: Palindrome 
 *
 * @file: palindome.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void palin(char * string, long len)
{
    char * strip = malloc((size_t)len * sizeof(char));
    if (strip == NULL)
    {
        return;
    }

    long index = 0;
    for (long i = 0; i < len; i +=1)
    {
        if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z'))
        {
            strip[index] = (char)tolower(string[i]);
            index += 1;
        }
    }

    bool same = true;
    for (long i = 0; i < index/2; i += 1)
    {
        if ((strip[i]) != (strip[index - i - 1]))
        {
            same = false;
        }
    }
    if (same)
    {
        cs1010_println_string("yes");
    }
    else
    {
        cs1010_println_string("no");
    }

    free(strip);
}

int main()
{
    char * string = cs1010_read_line();
    long len = (long)strlen(string);
    palin(string, len - 1);

    return 0;
}
