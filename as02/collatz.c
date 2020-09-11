/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Collatz 
 *
 * Read in a positive integer n from the standard input,
 * then, for each number k between number 1 .. n, transform
 * it into 1 based on the steps below:
 * - if k is even, k = k/2
 * - else, k = 3k + 1
 * Find the number k that requires the most number of steps
 * between 1 and n, and print both k and the number of steps
 * to standard output. If there are multiple numbers with
 * the same number of steps, we prefer to output the larger
 * among these numbers.
 *
 * @file: collatz.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"

// takes in an integer k and returns the total steps taken to reach 1 
long collatz_stepping(long k)
{
    long counter = 0;
    while (k != 1)
    {
        // if k is even
        if ((k % 2) == 0)
        {
            k /= 2;
        }
        else
        {
            k = (3 * k) + 1;
        }
        counter += 1;
    }
    return counter;
}

// takes in an integer 'number'
// prints out the largest number (1 .. number) that took the most steps in the collatz
// conjecture and prints out the most number of steps taken
void find_largest_collatz(long number)
{
    long max_num = 1;            // variable storing the largest number that took the most steps 
    long max_steps = 0;          // variable storing the most steps taken
    long current_steps;          // variable storing the current steps

    for (long k = 1; k <= number; k += 1)
    {
        current_steps = collatz_stepping(k);

        // found new largest steps
        if (current_steps >= max_steps)
        {
            max_steps = current_steps;
            max_num = k;
        }
    }

    cs1010_println_long(max_num);
    cs1010_println_long(max_steps);
}

int main() 
{
    long number = cs1010_read_long();       // variable to input the number
    
    // filter numbers less than or equals to 0
    if (number > 0)
    {
        find_largest_collatz(number);
    }
    return 0;
}
