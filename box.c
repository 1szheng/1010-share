/**
 * CS1010 Semester 1 AY20/21
 * Assignment 1: Box
 *
 * Read in three positive integer corresponding to the width,
 * height, and length of a box from the standard input, and
 * print the total surface area and the length of the diagonal
 * to the standard output.
 *
 * @file: box.c
 * @author: Wan Si Zheng (Group D05)
 */

#include "cs1010.h"
#include <math.h>

// returns the square value of num
double square(double num)
{
    return (num * num);
}

// returns the length of the hypotenuse
// square root of (base squared + height squared)
double hypotenuse_of(double base, long height)
{
    return sqrt(square(base) + square(height));
}

// returns area of rectangle
// base * height
long area_of_rectangle(long base, long height)
{
    return (base * height);
}

int main() 
{
    long* values = cs1010_read_long_array(3);               // stores values for length, width and height 
    if (values != NULL)
    {
        long length, width, height;                         // variables used for calculation
        
        length = values[0];
        width = values[1];
        height = values[2];

        // calculating the total surface area of box
        long area_TB = area_of_rectangle(length, width);    // area of top and bottom
        long area_S1 = area_of_rectangle(length, height);   // area of two sides
        long area_S2 = area_of_rectangle(width, height);    // area of the other two sides
        long total_area = (2 * area_TB) + (2 * area_S1) + (2 * area_S2);

        // calculating the hypotenuse between two farthest vertices
        double hypo_short = hypotenuse_of(length, width);       // length of the base's hypotenuse
        double hypo_long = hypotenuse_of(hypo_short, height);

        // printing results
        cs1010_print_long(total_area);
        cs1010_print_string(" ");
        cs1010_println_double(hypo_long);

    }
    free(values);
    return 0;
}
