/**
 * CS1010 Semester 1 AY20/21
 * Assignment 4: Mastermind
 *
 * This file contains an implementation of the Mastermind game.
 * This is a game whereby a four unit code is provided by the coder.
 * Each unit in the code is chosen from six different colors (cyan, 
 * green, red, blue, purple, orange). Repetition of the same color
 * is allowed. The colors are represented by their initials ('c', 'g',
 * 'r', 'b', 'p', 'o'). The code provided will be read from the
 * standard input.
 *
 * The code breaker will attempt to guess the code, and hints/pegs will be
 * provided after each attempt. Hints/pegs given are "the number of 
 * accurately guessed color and its position" and "the number of 
 * accurately guessed color" respesctively. These numbers are not double 
 * counted and amounts to four at most (e.g. 1 3). Hints provided and 
 * results are displayed on the standard output.
 *
 * @file: mastermind.c
 * @author: Wan Si Zheng (Group D05)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <string.h>

#define HINTS 4 

/**
 * Takes in the strings for code and guess. Checks guess against code to
 * generate hints for the mastermind game. Hints are based on "the number of
 * accurately guessed color and position" and the "number of accurately guessed
 * color" respectively. Hints are printed to the standard output. Two char
 * arrays will be generated within the function to keep track of the chars that
 * have been found before from guess, or checked against from code. This is to
 * prevent the double counting of hints in the event of repetition.
 *
 * @pre code is assumed to be not NULL and four characters made up of only 
 * ('c', 'g', 'r', 'b', 'p', 'o')
 * @pre guess is assumed to be not NULL and four characters made up of only 
 * ('c', 'g', 'r', 'b', 'p', 'o')
 *
 * @param[in] code The string that needs to be broken for the mastermind game
 * @param[in] guess The string that needs to be checked against code for hints
 */
void hint_generator(char* code, char* guess)
{
    long color_pos = 0;     // number of correctly guessed colors and positions
    long color = 0;         // number of correctly guessed colors

    char found_before[HINTS] = {0};     // colors from guess found before
    // to stop needless checking

    // fill up found_before with only those whose positions are guessed
    for (long i = 0; i < HINTS; i += 1)
    {
        if (*(code + i) == *(guess + i))
        {
            found_before[i] = *(guess + i);
            color_pos += 1;
        }
    }

    char checked_before[HINTS] = {0};   // colors from code checked before
    // to stop needless checking

    // find and count colors whose positions are incorrectly guessed
    // iterates through code up to 4 'hints'
    for (long i = 0;((color_pos + color) < HINTS) && i < HINTS; i += 1)
    {
        // if position not found previously to be same as code
        if (found_before[i] != *(code + i))
        {
            // iterates through guess up to 4 'hints'
            for (long iterator = 0;((color_pos + color) < HINTS) && iterator < HINTS; iterator += 1)
            {
                // found matching characters
                if (*(code + i) == *(guess + iterator))
                {

                    // if position of color in guess not found before, and
                    // if position of color in code not checked before
                    if ((found_before[iterator] == 0) && (checked_before[i] == 0))
                    {
                        found_before[iterator] = *(guess + iterator);
                        checked_before[i] = *(guess + iterator);
                        color += 1;
                    }
                }
            }
        }
    }

    // print hints
    cs1010_print_long(color_pos);
    cs1010_print_string(" ");
    cs1010_println_long(color);
}

/**
 * Emulates the guessing and checking of the mastermind game.
 * Takes in the four character code. Reads guesses from the code breaker
 * from standard input until code has been broken. Prints hints to standard
 * output based on the "number of accurately guessed color and position" and 
 * the "number of accurately guessed color" respectively. 
 *
 * @pre code is assumed to be not NULL and four characters made up of only 
 * ('c', 'g', 'r', 'b', 'p', 'o')
 * 
 * @param[in] code The code that needs to be broken for the mastermind game.
 */
void mastermind(char* code)
{
    char* guess;            // the four character guess code
    bool matched = false;   // true if guess == code

    while (!matched)
    {
        guess = cs1010_read_word();

        if (guess != NULL)
        {
            // if (guess == code), set matched to true and color_pos to HINTS
            // print results and exit while loop
            if (strcmp(guess, code) == 0)
            {
                long color_pos = HINTS; // total number of correct guesses
                long color = 0;     // number of correct - color_pos
                matched = true;

                // print results
                cs1010_print_long(color_pos);
                cs1010_print_string(" ");
                cs1010_println_long(color);
            }
            else
            {
                // else-case, generate hints
                hint_generator(code, guess);
            }
            free(guess);
        }
        else
        {   // memory allocation error, exit
            matched = true;
        }
    }
}

/**
 * Reads the secret code to be broken from standard input.
 
 * Given that there is no memory allocation error pass the 
 * code into mastermind to emulate the mastermind game. Thereafter,
 * free the memory allocated for the code read.
 *
 * @return Returns 1 if there is either a memory allocation error.
 * @return Returns 0 if no handled issues occur.
 */
int main()
{
    char* code = cs1010_read_word();
    if (code == NULL)
    {
        // memory allocation error, exit
        return 1;
    }
    mastermind(code);
    free(code);
    return 0;
}
