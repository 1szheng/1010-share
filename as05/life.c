/**
 * CS1010 Semester 1 AY20/21
 * Assignment 5: Life
 *
 * This file contains an implementation of the "Game of Life", a game_of_life
 * played on a two-dimensional orthogonal grid of square cells. Each cell has
 * two possible states: alive or dead. This game is played in iterations.
 * During each iteration, each cell becomes alive or dead depending on the
 * state of its four neighbouring cells in the previous iterations.
 *
 * In this implementation, the two-dimensional orthogonal grid is given by n
 * rows and m columns. Row 0 to (n-1) from top to bottom, and column 0 to 
 * (m-1) from left to right. A total of n x m cells. The neighbours of the
 * cell are the eight cells that are either horizontally, vertically or 
 * diagonally connected to the cell. An initial state is given, which each cell
 * marked as either alive or dead given by chars `#` and `.` respectively.
 * In each iteration, a cell may switch its state with reference to the state
 * of the previous iteration according to rules:
 *
 * > Any live cell with fewer than two live neighbors becomes dead
 * > Any live cell with two or three live neighbors remains alive.
 * > Any live cell with more than three live neighbors becomes dead.
 * > Any dead cell with exactly three live neighbors becomes alive
 * > Border cells, i.e., cells with row number 0 or $n-1$, or column 
 *   number 0 or $m-1$, are always dead. This is to simplify and 
 *   bound the universe.
 *
 * @file: life.c
 * @author: Wan Si Zheng (Group D05)
 */

#include <unistd.h>
#include "cs1010.h"

/**
 * Prints the contents of the given array to standard output.
 *
 * @pre array is assumed to be not NULL and represented by chars of `#`
 *	or `.` only.
 * @pre row > 2
 * @pre col > 2
 *
 * @param[in] array Stores the status of the cells in the grid.
 * @param[in] row The number of rows in the grid
 * @param[in] col The number of columns in the grid
 */
void print_grid(char **array, long row, long col)
{
	cs1010_clear_screen();
	for (long i = 0; i < row; i += 1)
	{
		for (long j = 0; j < col; j += 1)
		{
			putchar(array[i][j]);
		}
		cs1010_println_string("");
	}
	usleep(10 * 1000);
}

/**
 * Transfers the contents of updated_array into array from row and
 * column 1 to row and column (length-1).
 *
 * @pre array is assumed to be not NULL and represented by chars of `#`
 *	or `.` only.
 * @pre row > 2
 * @pre col > 2
 * @pre updated_array is assumed to be not NULL and represented by 
 * 	chars of `#` or `.` only.
 *
 * @param[in, out] array Stores the status of the cells in the grid.
 * @param[in] row The number of rows in the grid
 * @param[in] col The number of columns in the grid
 * @param[in] updated_array Stores the updated status of the cells.
 */
void transfer_content(char **array, long row, long col, char **updated_array)
{
	for (long i = 1; i < (row - 1); i += 1)
	{
		for (long j = 1; j < (col - 1); j += 1)
		{
			array[i][j] = updated_array[i - 1][j - 1];
		}
	}
}

/**
 * Updates the status of the cell, given by its row and column, by
 * checking the status of its surrounding eight cells in the previous
 * grid state. Returns a char that corresponds to the updated status.
 *
 * @pre array is assumed to be not NULL and represented by chars of `#`
 *	or `.` only.
 * @pre row > 2
 * @pre col > 2 
 *
 * @param[in] array Stores the status of the cells in the grid.
 * @param[in] row The number of rows in the grid
 * @param[in] col The number of columns in the grid
 *
 * @return Returns '#' if cell is alive based on rules, '.' otherwise.
 */
char dead_alive(char **array, long row, long col)
{
	long count = 0;
	long iter_row = row - 1;
	long iter_col = col - 1;
	
	// counting surrounding
	for (long i = 0; i < 3; i += 1)
	{
		for (long j = 0; j < 3; j += 1)
		{
			if (((iter_row + i) != row) || ((iter_col + j) != col))
			{
				if (array[iter_row + i][iter_col + j] == '#')
				{
					count += 1;
				}
			}
		}
	}

    char value = '.';

	// dead cell become alive
	if ((array[row][col] == '.') && (count == 3))
	{
		value = '#';
	}
	// live cells stays alive
	else if ((array[row][col] == '#') && (count == 2 || count == 3))
	{
		value = '#';
	}
	
	return value;
}

/**
 * Simulates the "Game of Life". A new array, updated_array, is
 * created to store the cell states in an iteration, based on the
 * cell's previous state found in array. At the end of each iteration,
 * the contents of updated_array will be transferred into array	such
 * that it can be used as the previous state for the next iteration.
 * Memory allocation for any explicitly allocated memory spaces will 
 * be freed at the end, or if any memory allocation error occurs. 
 * Return will be called in the event of an error.
 *
 * @pre array is assumed to be not NULL and represented by chars of `#`
 *	or `.` only.
 * @pre row > 2 && row == col
 * @pre col > 2 && row == col
 * @pre k assumed to be >= 1
 *
 * @param[in, out] array Stores the status of the cells in the grid.
 * @param[in] row The number of rows in the grid
 * @param[in] col The number of columns in the grid
 * @param[in] k The number of iterations to be performed
 */
void game_of_life(char **array, long row, long col, long k)
{
	// declare updated_array to store new iterations
	char **updated_array = malloc((size_t)(row - 2) * sizeof(char *));
	
	// memory allocation error
	if (updated_array == NULL)
	{
		return;
	}
	for (long i = 0; i < (row - 2); i += 1)
	{
		updated_array[i] = malloc((size_t)(col - 2) * sizeof(char));
		
		// memory allocation error
		if (updated_array[i] == NULL)
		{
			for (long exit_idx = i; exit_idx >= 0; exit_idx -= 1)
			{
				free(updated_array[exit_idx]);
				updated_array[exit_idx] = NULL;
			}
			free(updated_array);
			updated_array = NULL;
			return;
		}
	}
	
	for (long iter = 0; iter < k; iter += 1)
	{
		// iterate through row
		for (long row_i = 1; row_i < (row - 1); row_i += 1)
		{
			// iterate through columns
			for (long col_i = 1; col_i < (col - 1); col_i += 1)
			{
				updated_array[row_i - 1][col_i - 1] = dead_alive(array, row_i, col_i);
			}
		}
		transfer_content(array, row, col, updated_array);
		
		print_grid(array, row, col);
	}
	
	// clean up
	for (long clear = 0; clear < (row - 2); clear += 1)
	{
		free(updated_array[clear]);
		updated_array[clear] = NULL;
	}
	free(updated_array);
	updated_array = NULL;
}

int main()
{
	long n = cs1010_read_long();	// row
	long m = cs1010_read_long();	// column
	
	if ((n < 3) || (m < 3))
	{
		return 1;
	}
	
	long k = cs1010_read_long();
	
	char **array = malloc((size_t)n * sizeof(char *));
	
	// memory allocation error
	if (array == NULL)
	{
		return 2;
	}
	
	// initialize grid
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
	
	game_of_life(array, n, m, k);
	
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
