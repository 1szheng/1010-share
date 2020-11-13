/**
 * CS1010 Semester 1 AY18/19
 * Practical Exam 2: Marnell 
 *
 * @file: marnell.c
 * @author: XXX (Group YYY)
 */

#include "cs1010.h"
#include <stdbool.h>

bool is_prime(long n)
{
    if (n == 2)
    {
        return true;
    }

    if (n % 2 == 0)
    {
        return false;
    }

    long quotient;
    for (long i = 3; i * i <= n; i += 2)
    {
        quotient = n / i;

        if (quotient < i)
        {
            return true;
        }

        if (n == (quotient * i))
        {
            return false;
        }
    }
    return true;
}

void marnell(long n)
{
    long count = 0;

    for (long i = 2; i < n; i += 1)
    {
        if (is_prime(i))
        {
            for (long j = 2; (j * j) <= (n - i); j += 1)
            {
                if ((j * ((n - i)/j) == (n - i)) && (is_prime(j)) && (is_prime((n - i)/j)))
                {
                    count += 1;
                }
            }
        }
    }
    cs1010_println_long(count);
}

int main()
{
    long n = cs1010_read_long();

    marnell(n);
}
