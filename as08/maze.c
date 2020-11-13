/**
 * CS1010 Semester 1 AY20/21
 * Assignment 8: Maze
 *
 * This file contains an implementation of a method to find an exit to the maze
 * starting location being within the maze. The maze is simplified here to be a
 * grid of (m x n) cells. Each cell being denoted as '#' for a wall that cannot
 * be passed through, '.' for an empty space and '@' being the user's location
 * which is also counted as empty. An exit is described as the border cell such
 * as the top-most or bottom-most row, or left-most or right-most column. The
 * escapee may only move one step at a time, from one empty cell to an adjacent
 * empty cell. Two cells are adjacent if they share a common edge. 
 *
 * The method of pathing is by trial and error. The escapee first looks for an
 * adjacant cell that has yet to be visited in the order of up, right, down, 
 * then left to the cell that they are currently positioned in. If they find an
 * empty and unvisited adjacent cell, they move to that cell and now that cell
 * has been visited. If there are no empty and unvisited adjacent cells, they 
 * backtrack onto the path they came from while repeatedly looking for an empty
 * and unvisited adjacent cell. This allows for a systematic way of exploring
 * the maze with no repettion of visits except for backtracking. This method
 * stops when the exit is found or when the escapee ends up in their initial
 * position, which means there are no exits.
 *
 * This program reads from the standard input two positive integers m and n,
 * followed by m lines of n characters in each line which will represent the
 * maze. Only one escapee denoted by '@' will be present in the maze setup.
 * The program will then print out an animation of k iterations to the standard
 * output. The output will only contain m rows with n characters in each row,
 * with an additional row at last. After the maze has been printed, the number
 * of steps taken thus far will be printed. The maze will be represented in the
 * same manner as described before.
 *
 * @file: maze.c
 * @author: Wan Si Zheng (Group D05)
 */

#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define EMPTY '.'
#define WALL  '#'
#define USER  '@'

// declaration for use
bool find_exit(char **maze, bool **visited, long m, long n, long c_row, long c_col, long *steps);

/**
 * Print the maze to the screen.
 * 
 * @param[in] maze The 2D array representing the maze.
 * @param[in] nrows The number of rows of the maze.
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, long nrows, long steps) {
    cs1010_clear_screen();
    for (long i = 0; i < nrows; i += 1) {
        cs1010_print_string(maze[i]);
    }
    cs1010_println_long(steps);

    // sleep only if we are displaying in the terminal
    if (isatty(fileno(stdout))) {
        usleep(100*1000);
    }
}

/**
 * To move the position of the escapee in the direction given by nx_row and 
 * nx_col. Then, calls the four-directional pathing function to find the exit
 * recursively. If the pathing function does not return true, move the escapee
 * back to their original cell to backtrack.
 *
 * @pre maze    is not NULL
 * @pre visited is not NULL
 * @pre m       a positive integer
 * @pre n       a positive integer
 * 
 * @param[in, out]  maze    The 2D char array representing the maze
 * @param[in, out]  visited The 2D bool array recording the cells visited
 * @param[in]       m       The number of rows in the maze grid
 * @param[in]       n       The number of columns in the maze grid
 * @param[in]       c_row   The current row the escapee is on
 * @param[in]       c_col   The current column the escapee is on
 * @param[in, out]  steps   The number of steps taken thus far by the escapee
 * @param[in]       nx_row  The row-direction to move in : {-1, 0, 1}
 * @param[in]       nx_col  The column-direction to move in : {-1, 0, 1}
 *
 * @return  Returns true if the exit is found, false otherwise
 */
bool valid_step(char **maze, bool **visited, long m, long n, long c_row, long c_col, long *steps, long nx_row, long nx_col)
{
	// moving forwards
	maze[c_row][c_col] = EMPTY;
	maze[c_row + nx_row][c_col + nx_col] = USER;
	*steps += 1;
	
	print_maze(maze, m, *steps);
	
    // four-directional pathing
	if (find_exit(maze, visited, m, n, (c_row + nx_row), (c_col + nx_col), steps))
	{
		return true;
	}
	
	// stepping backwards
	maze[c_row][c_col] = USER;
	maze[c_row + nx_row][c_col + nx_col] = EMPTY;
	*steps += 1;

	print_maze(maze, m, *steps);
	
	return false;
}

/**
 * To find an exit to the maze by checking the four directions in order of up,
 * left, down, and right. Path towards the direction if the cell is found to be
 * unvisited and empty.
 *
 * @pre maze    is not NULL
 * @pre visited is not NULL
 * @pre m       a positive integer
 * @pre n       a positive integer
 * 
 * @param[in, out]  maze    The 2D char array representing the maze
 * @param[in, out]  visited The 2D bool array recording the cells visited
 * @param[in]       m       The number of rows in the maze grid
 * @param[in]       n       The number of columns in the maze grid
 * @param[in]       c_row   The current row the escapee is on
 * @param[in]       c_col   The current column the escapee is on
 * @param[in, out]  steps   The number of steps taken thus far by the escapee
 *
 * @return  Returns true if the exit is found, false otherwise
 */
bool find_exit(char **maze, bool **visited, long m, long n, long c_row, long c_col, long *steps)
{
	if (c_row == 0 || c_row == (m - 1) || c_col == 0 || c_col == (n - 1))
	{
		return true; // found exit
	}
	
	visited[c_row][c_col] = true; // mark current as visited

	long direction[4][2] = {{-1, 0}, {0, 1}, {1,0}, {0, -1}};
	for (long i = 0; i < 4; i += 1)
	{	
		// moving up
		long nx_row = direction[i][0];   // next row
		long nx_col = direction[i][1];    // next column
		if (!visited[c_row + nx_row][c_col + nx_col] && maze[c_row + nx_row][c_col + nx_col] == EMPTY)
		{
			if (valid_step(maze, visited, m, n, c_row, c_col, steps, nx_row, nx_col))
			{
				return true;
			}
		}
	}
	return false;
}

/**
 * Creates and initialises a 2D bool array representing the cells that
 * have been visited before.
 *
 * @pre m a positive integer
 *
 * @param[in] m The number of rows in the maze grid
 *
 * @return The memory address to the initialised array or NULL if unsuccessful
 */
bool **init_visited(long m, long n)
{
	bool **visited = malloc((size_t)m * sizeof(bool *));
	if (visited == NULL)
	{
		cs1010_println_string("visited memory allocation error");
		return NULL;
	}
	for (long i = 0; i < m; i += 1)
	{
		visited[i] = calloc((size_t)n, sizeof(bool));
		if (visited[i] == NULL)
		{
			for (long j = 0; j < i; j += 1)
			{
				free(visited[j]);
			}
			free(visited);
			cs1010_println_string("visited memory allocation error");
			return NULL;
		}
	}
	return visited;
}

/**
 * Creates and initialises a 2D char array representing the maze, with
 * characters from the standard input.
 *
 * @pre m a positive integer
 *
 * @param[in] m The number of rows in the maze grid
 *
 * @return The memory address to the initialised maze or NULL if unsuccessful
 */
char **init_maze(long m)
{
    char **maze = malloc((size_t)m * sizeof(char *));
	if (maze == NULL)
	{
		cs1010_println_string("maze memory allocation error");
		return NULL;
	}

	for (long i = 0; i < m; i += 1)
	{
		maze[i] = cs1010_read_line();
		if (maze[i] == NULL)
		{
			for (long j = 0; j < i; j += 1)
			{
				free(maze[j]);
			}
			free(maze);
			cs1010_println_string("maze memory allocation error");
			return NULL;
		}
	}
    return maze;
}

int main() 
{
	long m = cs1010_read_long();
	long n = cs1010_read_long();
	
	char **maze = init_maze(m);
	if (maze == NULL)
	{
        return 1;
	}
	
	bool **visited = init_visited(m, n);
	if (visited == NULL)
	{
		for (long i = 0; i < m; i += 1)
		{
			free(maze[i]);
		}
		free(maze);
		return 1;
	}
	
    // finding Scully 
	long row = 0;
	long col = 0;
	for (long i = 0; row == 0 && i < m; i += 1)
	{
		for (long j = 0; col == 0 && j < n; j += 1)
		{
			if (maze[i][j] == USER)
			{
				row = i;
				col = j;
			}
		}
	}

	long steps = 0;
	print_maze(maze, m, steps);
	find_exit(maze, visited, m, n, row, col, &steps);
	
    // clean up
	for (long i = 0; i < m; i += 1)
	{
		free(maze[i]);
		free(visited[i]);
	}
	free(maze);
	free(visited);

    return 0;
}
