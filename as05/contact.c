/**
 * CS1010 Semester 1 AY20/21
 * Assignment 5: Contact
 *
 * This file contains an implementation of contact tracing.
 * This implementation seeks to track if there has been direct contact
 * between two individuals A and B, and if there is a third individual C
 * that both A and B got into contact with: between (A and C) and (B and C).
 *
 * This implementation assumes that "contact" is a symmetric relation. If A
 * has been in contact with B, then B has been in contact with A. Therefore,
 * this contact tracing relationship between k number of people is represented
 * as a lower triangular matrix. Each element of the matrix is either a char
 * '0' or '1', representing a connection and no connection respectively. The
 * first row of the matrix will be of length one, increasing per row, until the
 * last row, k. The last character of each string (i.e. the diagonal of the
 * matrix) is '1' since everyone has contact with themselves. Each individual
 * is represented by an id, from 0 to k. Individuals with id i will have their
 * information stored in Row i and Column i. If Row i and Column j is '1', 
 * individual with id i has been in contact with individual with id j.
 *
 * @file: contact.c
 * @author: Wan Si Zheng (Group D05)
 */ 

#include "cs1010.h"
#include <stdbool.h>

/**
 * Takes in an array that holds the contact statuses of len number of
 * people. Takes in id_one and id_two and check if there has been direct,
 * indirect, or no contact between the two people. Prints out the contact
 * status to the standard output.
 *
 * @pre array is assumed to be not NULL and represented in the lower
 *  triangular matrix of '0's and '1's as mentioned in the abstract.
 * @pre len > 0
 * @pre id_two >= id_one
 *
 * @param[in] array Stores the lower triangular matrix with contact statuses.
 * @param[in] len Length of the array, total number of people in the array.
 * @param[in] id_one ID of person one to be checked.
 * @param[in] id_two ID of person two to be checked.
 */
void check_contact(char **array, long len, long id_one, long id_two)
{
    // if direct contact, else potential indirect contact
    if (array[id_two][id_one] == '1')
    {
        cs1010_println_string("direct contact");
    }
    else
    {
        long indirect_id;
        bool found = false;

        for (long i = 0; (!found) && (i < len); i += 1)
        {
            // checks for i <= id_two and i > id_two are different
            if (i <= id_two)
            {
                if (array[id_two][i] == '1')
                {
                    // checks for i < id_one and i > id_one is different
                    // i != id_one as its not direct contact
                    if (i < id_one)
                    {
                        if (array[id_two][i] == array[id_one][i])
                        {
                            indirect_id = i;
                            found = true;
                        }
                    }
                    else
                    {
                        if (array[id_two][i] == array[i][id_one])
                        {
                            indirect_id = i;
                            found = true;
                        }
                    }
                }
            }
            else
            {
                if ((array[i][id_one] == '1') && (array[i][id_two] == '1'))
                {
                    indirect_id = i;
                    found = true;
                }
            }
        }

        if (found)
        {
            cs1010_print_string("contact through ");
            cs1010_println_long(indirect_id);
        }
        else
        {
            cs1010_println_string("no contact");
        }
    }
}

int main()
{
    long len = cs1010_read_long();

    if (len > 0)
    {
        char **array = malloc((size_t)len * sizeof(char *));

        // memory allocation error
        if (array == NULL)
        {
            return 1;
        }

        // initialize contact list
        for (long i = 0; i < len; i += 1)
        {
            array[i] = cs1010_read_line();

            // memory allocation error
            if (array[i] == NULL)
            {
                for (long j = i; j >= 0; j -= 1)
                {
                    free(array[j]);
                }
                free(array);
                return 1;
            }
        }

        long id_one = cs1010_read_long();
        long id_two = cs1010_read_long();

        if (id_two > id_one)
        {
            check_contact(array, len, id_one, id_two);
        }
        else
        {
            check_contact(array, len, id_two, id_one);
        }

        // freeing memory
        for (long i = 0; i < len; i += 1)
        {
            free(array[i]);
        }
        free(array);
    }
    return 0;
}
