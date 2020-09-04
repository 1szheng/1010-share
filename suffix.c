/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Suffix
 *
 * Read in a number and prints out the number with the appropriate suffix.
 *
 * @file: suffix.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"

// takes in integer n and prints out with trailing suffix
void print_with_suffix(long n)
{
    // filter negative cases
    // ordinal suffix for negatives do not exist
    if (n >= 0)
    {
        cs1010_print_long(n);
       
        // 0th case
        if (n == 0)
        {
            cs1010_println_string("th");
        }

        // positive case
        else
        {
            // checking if last digit is 1
            if ((n % 10) == 1)
            {
                // checking if second last digit is 1
                // thus last two digits are 11
                if (((n / 10) % 10) == 1)
                {
                    cs1010_println_string("th");    
                }
                else
                {
                    cs1010_println_string("st");
                }
            }

            // checking if last digit is 2
            else if ((n % 10) == 2)
            {
                // checking if second last digit is 1
                // thus last two digits are 12
                if (((n / 10) % 10) == 1)
                {
                    cs1010_println_string("th");
                }
                else
                {
                    cs1010_println_string("nd");
                }
            }

            // checking if last digit is 3
            else if ((n % 10) == 3)
            {
                // checking if second last digit is 1
                // thus last two digits are 13
                if (((n / 10) % 10) == 1)
                {
                    cs1010_println_string("th");
                }
                else
                {
                    cs1010_println_string("rd");
                }
            }

            // any last digit that is not 1, 2 or 3
            else
            {
                cs1010_println_string("th");
            }
        }
    }
}


int main() 
{
    long number = cs1010_read_long();
    print_with_suffix(number);

    return 0;
}
