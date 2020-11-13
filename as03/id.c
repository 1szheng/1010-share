/**
 * CS1010 Semester 1 AY20/21
 * Assignment 3: ID
 *
 * Read in a number and print out the check code 
 * according to NUS student ID algorithm.
 *
 * @file: id.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"

// takes in an integer and returns the sum of each number in it
long find_sum(long integer)
{
    long sum = 0;       // variable storing the sum of the numbers
    while (integer > 0)
    {
        sum += (integer % 10);
        integer /= 10;
    }
    return sum;
}

// takes in an integer and prints the check code
void print_check_code(long integer)
{
    char check_code[13] = {'Y', 'X', 'W', 'U', 'R', 'N', 'M', 'L', 'J', 'H', 'E', 'A', 'B'};

    // finding R value of integer
    long sum = find_sum(integer);
    long R = sum % 13;

    // printing check code
    putchar(check_code[R]);
    cs1010_println_string("");
}
int main()
{
    long integer = cs1010_read_long();  // storing input for an integer
    print_check_code(integer);

    return 0;
}
