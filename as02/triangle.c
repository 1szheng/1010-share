#include "cs1010.h"
/**
 * CS1010 Semester 1 AY20/21
 * Assignment 2: Triangle
 *
 * Read in a positive integer h from standard input and 
 * print an equlateral triangle of height h.
 *
 * @file: triangle.c
 * @author: Wan Si Zheng (Group D05)
 */

// takes in the number of spaces needed to be printed and prints them
void print_white_space(long spaces)
{
    for (long counter = 0; counter < spaces; counter += 1)
    {
        cs1010_print_string(" ");
    }
}

// takes in the number of '#' needed to be printed and prints them
void print_hex(long hex)
{
    for (long counter = 0; counter < hex; counter += 1)
    {
        cs1010_print_string("#");
    }
}

// takes in an integer height and print an isosceles triangle
void triangle(long height)
{
    long LEN = (2 * height) - 1;            // stores the number of characters to be printed
    long hex;                               // stores the number of '#' needed to be printed
    long spaces;                            // stores the number of spaces needed to be printed

    // loop through and printing each line
    for (long h = 1; h <= height; h += 1)
    {
        hex = ((h - 1) * 2) + 1;
        spaces = ((LEN - hex)/2);

        print_white_space(spaces);
        print_hex(hex);
        print_white_space(spaces);
        cs1010_println_string("");
    }
}

int main()
{
    long height = cs1010_read_long();       // variable to input height

    if (height > 0)
    {
        triangle(height);
    }
    return 0;
}
