/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Prime
 *
 * Reads in an integer n from standard input and print 
 * the largest prime smaller or equal to n.
 *
 * @file: prime.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

// takes in an integer (>2) and checks if it is a prime
// returns true if number is a prime, otherwise false
bool check_prime(long number)
{
    // loop through odd numbers, up to square root of number
    // to check if number is perfectly divisible
    for (long counter = 3; (counter * counter) <= number; counter += 2)
    {
        long quotient = (number / counter);

        if (quotient < counter)
        {
            return true;
        }

        if (number == (quotient * counter))
        {
            return false;
        }
    }
    return true;
}

// takes in an integer number and print out the largest prime number smaller or equals to it
void prime(long number)
{
    if (number != 2)
    {
        bool is_prime;

        // the only even prime is 2, thus make the number odd and check for prime
        if ((number % 2) == 0)
        {
            number -= 1;
            is_prime = check_prime(number);
        }
        else
        {
            is_prime = check_prime(number);
        }

        // loop to find the next largest prime smaller than number
        while (is_prime != true)
        {
            number -= 2;
            is_prime = check_prime(number);
        }
    }

    cs1010_println_long(number);
}

int main()
{
    long number = cs1010_read_long();     // variable to input number

    if (number > 1)
    {
        prime(number);
    }
    return 0;
}
