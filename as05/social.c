/**
 * CS1010 Semester 1 AY20/21
 * Assignment 5: Social
 *
 * This file contains an implementation of the six degree
 * of seperation. It states that everyone in the world is
 * connected to every other person by at most 6 hops. Suppose
 * that a person A is a friend of a person B, then we say 
 * that A is one hop away from B. Consider a friend of B,
 * say C, who is not a friend of A. So C is a friend of a
 * friend of A. We say that C is two hops away from A.  Six
 * degrees of separation generally means there is a chain of
 * friendship that can connect any two people in the world 
 * with no more than 6 hops. This file will compute the chain
 * of friendship up to a given k degree, rather than just 6.
 *
 * This implementation assumes that friendship is bi-directional
 * i.e if A is a friend of B, then B is a friend of A. This network
 * will be represented in a lower triangular matrix between n number 
 * of people. Each element of the matrix is either a char '0' or '1',
 * representing a friendship and no friendship respectively. The first
 * row of the matrix will be of length one, increasing per row, until 
 * the last row, n. The last character of each string (i.e. the diagonal 
 * of the matrix) is '1' since everyone has contact with themselves. 
 * Each individual is represented by an id, from 0 to k. Individuals 
 * with id i will have their information stored in Row i and Column i.
 * If Row i and Column j is '1', individual with id i has been in 
 * contact with individual with id j.
 *
 * @file: social.c
 * @author: Wan Si Zheng (Group D05)
 */
 
#include <stdio.h>
#include <stdbool.h>
#include "cs1010.h"
 
/**
 * Takes in an array that holds the friendship status of n number of
 * people. Prints out the char contents of the array. 
 *
 * @pre n > 0
 * @pre array is assumed to be not NULL and represented in the lower
 *  triangular matrix of '0's and '1's as mentioned in the abstract.
 *
 * @param[in] n Number of people in the array. 
 * @param[in] array The array that to be printed.
 */
 void print_array(long n, char **array)
{
	for (long i = 0; i < n; i += 1)
	{
		for (long j = 0; j <= i; j += 1)
		{
			putchar(array[i][j]);
		}
		cs1010_println_string("");
	}
}
 
/**
 * Takes in an array that holds the friendship status of n number of
 * people. Takes in id, the individual whose degree 1 friendship needs
 * to be found and stored into i_contacts. Total number of friends found
 * will be tracked.
 *
 * @pre n > 0
 * @pre array is assumed to be not NULL and represented in the lower
 *  triangular matrix of '0's and '1's as mentioned in the abstract.
 * @pre id <= n
 * @pre i_contacts is assumed to be not NULL and represented only by chars
 *	of '0's and '1's.
 *
 * @param[in] n Number of people in the array. 
 * @param[in] array The array that contains the original friendship status.
 * @param[in] id The individual whose friendship status is being compiled.
 * @param[in, out] i_contacts The array which contains id's friendships.
 *
 * @return Return true if all n friendships found.
 * @return Return false if not all n friendships found.
 */
 bool fill_deg_one(long n, char **array, long id, char *i_contacts)
{
	long count = 0;	// number of friends found
	
	// iterate through i_contacts
	for (long i = 0; i < n; i += 1)
	{
		if (i <= id)
		{
			if (array[id][i] == '1')
			{
				count += 1;
				i_contacts[i] = '1';
			}
		}
		else
		{
			if (array[i][id] == '1')
			{
				count += 1;
				i_contacts[i] = '1';
			}
		}
	}
	
	if (count == n)
	{
		return true;
	}
	return false;
}
 
/**
 * Takes in an array that holds the friendship status of n number of
 * people. Takes in id_two, an individual, and i_contacts, an array
 * containing the friendship status of "some individual". Check for direct
 * friendship between id_two and those found in i_contacts. Essentially
 * acts as a third party friendship finder between "some individual" and
 * id_two.
 *
 * @pre n > 0
 * @pre array is assumed to be not NULL and represented in the lower
 *  triangular matrix of '0's and '1's as mentioned in the abstract.
 * @pre id_two <= n
 * @pre i_contacts is assumed to be not NULL and represented only by chars
 *	of '0's and '1's.
 *
 * @param[in] n Number of people in the array. 
 * @param[in] array The array that contains the original friendship status.
 * @param[in] id_two The individual whose direct friendship is being checked.
 * @param[in] i_contacts An array of friends for id_two to be checked against.
 *
 * @return Return true if direct friendship found.
 * @return Return false if direct friendship not found.
 */
 bool find_connection(long n, char **array, long id_two, char *i_contacts)
{
	// iterate through i_contacts
	for (long i = 0; i < n; i += 1)
	{
		if (i_contacts[i] == '1')
		{
			if (i < id_two)
			{
				if (array[id_two][i] == '1')
				{
					return true;
				}
			}
			else
			{
				if (array[i][id_two] == '1')
				{
					return true;
				}
			}
		}
	}
	return false;
}
 
/**
 * Takes in an array that holds the friendship status of n number of
 * people. Takes in i_contacts, the current degree of computed friendships,
 * where the next degree of friendship is to be stored.
 * Creates a temporary array to store the newly found degree of friendship,
 * to avoid unintended hops. Contents of temporary array will be transferred
 * into i_contacts at the end. Keeps track of a count, which counts the number
 * of people found to share friendship with id, inclusive.
 *
 * @pre n > 0
 * @pre array is assumed to be not NULL and represented in the lower
 *  triangular matrix of '0's and '1's as mentioned in the abstract.
 * @pre i_contacts is assumed to be not NULL and represented only by chars
 *	of '0's and '1's.
 *
 * @param[in] n Number of people in the array. 
 * @param[in] array The array that contains the original friendship status.
 * @param[in, out] i_contacts The array which contains some id's friendships
 *
 * @return Return true if all n friendships found within i_contacts
 *  or if memory allocation error occurs.
 * @return Return false if not all n friendships found.
 */
 bool next_degree(long n, char **array, char *i_contacts)
{
	char *temp_row = calloc((size_t)n, sizeof(char));
	if (temp_row == NULL)
	{
		return true;	// to exit faster loops faster
	}
	
	bool third_party;
	long count = 0;
	
	// iterate through i_contacts and find third_party for missing ids
	for (long i = 0; i < n; i += 1)
	{
		if (i_contacts[i] != '1')
		{
			third_party = find_connection(n, array, i, i_contacts);
			
			if (third_party)
			{
				temp_row[i] = '1';
				count += 1;
			}
		}
		else
		{
			count += 1;
		}
	}
	
	// update content of i_contacts
	for (long j = 0; j < n; j += 1)
	{
		if (temp_row[j] == '1')
		{
			i_contacts[j] = '1';
		}
	}
	
	free(temp_row);
	temp_row = NULL;
	
	if (count == n)
	{
		return true;
	}
	return false;
}
 
/**
 * Takes in updated_array which holds the computed friendship status
 * of n number of people. Takes in id, the individual whose friendship
 * have been computed and the computed friendship array i_contacts.
 * Contents from i_contacts are transferred into the updated_array.
 *
 * @pre n > 0
 * @pre updated_array is assumed to be not NULL and represented in the lower
 *  triangular matrix of '0's and '1's as mentioned in the abstract.
 * @pre id <= n
 * @pre i_contacts is assumed to be not NULL and represented only by chars
 *	of '0's and '1's.
 *
 * @param[in] n Number of people in the array. 
 * @param[in, out] updated_array The array that contains k degree friendships
 * @param[in] id The individual whose friendship status is being updated
 * @param[in] i_contacts The array which contains id's friendships
 */
 void transfer_to_new(long n, char **updated_array, long id, char *i_contacts)
{
	for (long i = 0; i < n; i += 1)
	{
		if ((i_contacts[i] == '1') && (i >= id))
		{
		  updated_array[i][id] = '1';
		}
	}
}
 
/**
 * Takes in an array that holds the friendship status of n number of
 * people, and the degree of friendships to be computed, k. Creates
 * a new triangular matrix to hold the computed friendship status to
 * avoid unintended hops between individuals. Prints the friendship
 * status to the standard output via the print_array function once
 * computed. Memory allocation for any explicitly allocated memory
 * spaces will be freed at the end, or if any memory allocation error
 * occurs. Return will be called in the event of an error.
 *
 * @pre n > 0
 * @pre array is assumed to be not NULL and represented in the lower
 *  triangular matrix of '0's and '1's as mentioned in the abstract.
 * @pre k > 1
 *
 * @param[in] n Length of the array, total number of people in the array.
 * @param[in] array Stores the lower triangular matrix with friendship statuses.
 * @param[in] k The degree of friendship to be computed.
 */
 void social(long n, char **array, long k)
{
	// declare updated_array to store computed friendships
	char **updated_array = malloc((size_t)n * sizeof(char *));
	if (updated_array == NULL)
	{
		return;
	}
	for (long index = 0; index < n; index += 1)
	{
		updated_array[index] = malloc((size_t)(index + 1) * sizeof(char));
		
		// memory allocation error
		if (updated_array[index] == NULL)
		{
			for (long exit_idx = index; exit_idx >= 0; exit_idx -= 1)
			{
				free(updated_array[exit_idx]);
				updated_array[exit_idx] = NULL;
			}
			free(updated_array);
			updated_array = NULL;
			return;
		}
	}
	
	// initialize updated_array to char '0'
	for (long init_row = 0; init_row < n; init_row += 1)
	{
		for (long init_col = 0; init_col <= init_row; init_col += 1)
		{
			updated_array[init_row][init_col] = '0';
		}
	}
	
	// declare i_contacts to store friendships of id i in a row
	char *i_contacts = malloc((size_t)n * sizeof(char));
	
	if (i_contacts != NULL)
	{
		// loops through rows to find kth degree friendship
		for (long i = 0; i < n; i += 1)
		{
			for (long zero = 0; zero < n; zero += 1)
			{
				i_contacts[zero] = '0';
			}
			
			bool found = false;	// true when i_contacts fully filled
			
			// fill i_contacts with degree 1 friendship
			found = fill_deg_one(n, array, i, i_contacts);

			// loop from degree 1 up to degree k to fill i_contacts
			for (long j = 1; (!found) && j < k; j += 1)
			{
				found = next_degree(n, array, i_contacts);
			}
			
			transfer_to_new(n, updated_array, i, i_contacts);
		}
		print_array(n, updated_array);
	}
	
	// clean up
	free(i_contacts);
	i_contacts = NULL;
	for (long clear = 0; clear < n; clear += 1)
	{
		free(updated_array[clear]);
		updated_array[clear] = NULL;
	}
	free(updated_array);
	updated_array = NULL;
}
 
int main()
{
	long n = cs1010_read_long();	// num of people
	long k = cs1010_read_long();	// degree of contact

	// empty array
	if (n < 1)
	{
		return 1;
	}

	char **array = malloc((size_t)n * sizeof(char *));

	// memory allocation error
	if (array == NULL)
	{
		return 2;
	}
	
	// initialize contact list
	for (long i = 0; i < n; i += 1)
	{
		array[i] = cs1010_read_line();

		// memory allocation error
		if (array[i] == NULL)
		{
			for (long j = i; j >= 0; j -= 1)
			{
				free(array[j]);
				array[j] = NULL;
			}
			free(array);
			array = NULL;
			return 2;
		}
	}
	
	// degree 1 relation are direct contacts
	if (k <= 1)
	{
		print_array(n, array);
	}
	else
	{
		social(n, array, k);
	}
	
	// freeing memory
	for (long i = 0; i < n; i += 1)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
	return 0;
}
