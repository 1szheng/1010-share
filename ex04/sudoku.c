/**
 * CS1010 Semester 1 AY20/21
 * Exercise 5: Sudoku
 *
 * TODO(by student): Brief description of the purpose 
 * of this program.
 *
 * @file: sudoku.c
 * @author: XXX (Group XXX)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

#define EMPTY '.'

void print_row(char *row) {
    for (int i = 0; i < 9; i += 1) {
        putchar(row[i]);
        if (i == 2 || i == 5) {
            cs1010_print_string("│");
        }
    }
    putchar('\n');
}

void print_sudoku(char **puzzle) {
    cs1010_clear_screen();
    for (int i = 0; i < 9; i += 1) {
        print_row(puzzle[i]);
        if (i == 2 || i == 5) {
            cs1010_println_string("───┼───┼───");
        }
    }
    if (isatty(fileno(stdout))) {
        usleep(10*500);
    }
}

bool threat_box(char **board, long row, long col, long num)
{
    long t_row = row - (row % 3);
    long t_col = col - (col % 3);

    for (long i = 0; i < 3; i += 1)
    {
        for (long j = 0; j < 3; j += 1)
        {
            if (board[t_row + i][t_col + j] != EMPTY && board[t_row + i][t_col + j] == (num + '0'))
            {
                return true;
            }
        }
    }
    return false;
}

bool threat_col(char **board, long n, long num)
{
    for (long i = 0; i < 9; i += 1)
    {
        if (board[i][n] != EMPTY && board[i][n] == (num + '0'))
        {
            return true;
        }
    }
    return false;
}

bool threat_row(char **board, long m, long num)
{
    for (long i = 0; i < 9; i += 1)
    {
        if (board[m][i] != EMPTY && board[m][i] == (num + '0'))
        {
            return true;
        }
    }
    return false;
}

bool threat(char **b, long m, long n, long num)
{
    return (threat_row(b, m, num) || threat_col(b, n, num) || threat_box(b, m, n, num));
}

bool solve(char **board, long row, long col)
{
    if (row > 8)
    {
        return true; // filled all
    }
    if (board[row][col] != EMPTY)
    {
        if (col == 8)
        {
            row += 1;
        }
        return solve(board, row, (col + 1) % 9);
    }
    for (long i = 1; i <= 9; i += 1)
    {
        if (!threat(board, row, col, i))
        {
            board[row][col] = (char)(i + '0');
            print_sudoku(board);

            long next_row = row;
            if (col == 8)
            {
                if (row == 8)
                {
                    return true;
                }
                next_row += 1;
            }
            if (solve(board, next_row, (col + 1) % 9))
            {
                return true;
            }
            board[row][col] = EMPTY;
        }
    }
    return false;
}

char **read_array(long m)
{
    char **mem = malloc((size_t)m * sizeof(char *));
    if (mem == NULL)
    {
        return NULL;
    }
    for (long i = 0; i < m; i += 1)
    {
        mem[i] = cs1010_read_line();
        if (mem[i] == NULL)
        {
            for (long j = 0; j < i; j += 1)
            {
                free(mem[i]);
            }
            free(mem);
            return NULL;
        }
    }
    return mem;
}

void free_2d(void **a, long m)
{
    for (long i = 0; i < m; i += 1)
    {
        free(a[i]);
    }
    free(a);
}

int main()
{
    char **board = read_array(9);
    if (board == NULL)
    {
        return 1;
    }

    print_sudoku(board);
    if (solve(board, 0, 0))
    {
        print_sudoku(board);
    }
    else
    {
        cs1010_println_string("no");
    }

    free_2d((void **)board, 9);
    return 0;
}
