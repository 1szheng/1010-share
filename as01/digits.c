/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Digits
 *
 * Read in a positive integer from the standard input and print
 * the sum of the square of each digit in the integer to the standard output.
 *
 * @file: digits.c
 * @author: Wan Si Zheng (Group D05)
 */

#include "cs1010.h"

// returns the sum of the square values of each digit found in the integer
long sum_of_squares(long num)
{
    // base case, left 1 digit
    if ((num/10) == 0)
    {
        return (num * num);
    }

    long digit = num % 10;          // the last digit of the integer
    long square = digit * digit;    // the square of the last digit
    return (square + sum_of_squares(num/10));   // dividing by 10 to truncate last digit
}

int main()
{
    long integer = cs1010_read_long();
    if (integer >= 0)               // filter out negative integers
    {
        long sum = sum_of_squares(integer);
        cs1010_println_long(sum);
    }
    return 0;
}
