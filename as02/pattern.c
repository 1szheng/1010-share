/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Pattern
 *
 * Read in two positive integers: an interval n (n >= 1) 
 * and the height of the triangle h.  Then draw a triangle
 * according to a given pattern.  
 *
 * @file: pattern.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

// takes in the number of spaces needed to be printed and prints them
void print_white_space(long spaces)
{
    for (long counter = 0; counter < spaces; counter += 1)
    {
        cs1010_print_string(" ");
    }
}

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

// takes in integer n and row
// returns the leading n value for the given row
long find_leading_n(long n, long row)
{
    long lead_multiple = 0;         // variable storing the multiple to find the leading n
    
    for (long counter = (row - 1); counter > 0; counter -= 1)
    {
        lead_multiple += counter;
    }

    return ((lead_multiple * n) + 1);
}

// takes in the leading n value, row, n, and the total length of characters required to be printed for given row
// prints out the row of characters consisting '#' if cell contains (prime or 1) and ' ' otherwise
void print_parallax_row(long leading_n, long row, long n, long LEN_print)
{
    long current_n;     // storing the variable of the current n or leading n of the given cell
    bool isPrime;       // storing the primeness of current_n, false until proven otherwise

    // traversing the row
    for (long cell = 0; cell < LEN_print; cell += 1)
    {
        current_n = leading_n + cell;       // the leading n value for each cell
        isPrime = false;

        // traversing inside each cell, to check for prime, or until isPrime is true
        for (long integer = 0; ((integer < n) && (!isPrime)); integer += 1)
        {
            // 1 is treated as a prime for parallax compression's purpose
            if (current_n <= 2)
            {
                isPrime = true;
            }

            // conditions for check: not 1, not 2, not divisible by 2
            if ((!isPrime) && ((current_n % 2) != 0))
            {
                // if true, set isPrime to true
                if (check_prime(current_n))
                {
                    isPrime = true;
                }
            }

            // increment current_n by row if not prime
            if (!isPrime)
            {
                current_n += row;
            }      
        }

        // prints out '#' or ' ' depending on its primeness
        if (isPrime)
        {
            cs1010_print_string("#");
        }
        else
        {
            cs1010_print_string(" ");
        }
    }
}

// takes in integer n and height of triangle to be printed
// prints out the triangle with the "Parallax Compression" pattern based on interval n
void pattern(long n, long height)
{
    long LEN = (2 * height) - 1;    // stores the total number of characters to be printed
    long num_of_p_hexes;            // stores the number of potential '#' to be printed
    long spaces;                    // stores the number of white space needed to be printed

    // traversing the height
    for (long row = 1; row <= height; row += 1)
    {
        num_of_p_hexes = ((row - 1) * 2) + 1;
        spaces = (LEN - num_of_p_hexes)/2;

        long leading_n = find_leading_n(n, row);    // stores the value of the leading n for the given row

        // printing the parallax triangle
        print_white_space(spaces);
        print_parallax_row(leading_n, row, n, num_of_p_hexes);
        print_white_space(spaces);
        cs1010_println_string("");
    }
}

int main()
{
    long* values = cs1010_read_long_array(2);   // variable to store inputs for interval n and height

    // valid inputs
    if ((values != NULL) && (values[0] > 0) && (values[1] > 0))
    {
        long n = values[0];
        long height = values[1];

        pattern(n, height);
    }

    free(values);
    return 0;
}
