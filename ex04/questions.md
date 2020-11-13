Question 1: Fill
----------------

Julia is attending a drawing class today. She has already
completed her work, but the teacher is not satisfied with
her choice of colors and wants her to re-color some parts.
She asks you, a programming genius, to help.

Julia's drawing can be simplified as a 2D array of size
m x n, with each color represented by a character. The
drawing consists of several objects. Each object can be
viewed as connected areas of cells of the same color. Two
cells are connected if they share a common edge, i.e. a
cell will have at most 4 connected cells.

Write a program, `fill.c`, to help Julia re-color her
drawing according to her teacher's requirement. It reads
from standard input two positive integers m and n in
the first line, followed by m lines of strings. Each
string is of length n.  The next line is a positive
integer q, which is the number of color changes the
teacher requires. Following this, there are q lines.
Each line has two integers x, y, and a character c. It
means to color the object containing pixel (x, y) to the
color c. We denote the top left pixel to be (0,0) and the
indices increases towards the right and down.

The program shall prints to standard output, the drawing
after re-coloring the objects according to the teacher's
commands according to the order of the input. Note that
one object can be re-colored multiple times.

You should use recursion to complete the coloring process.

Your solution must take no more than O(mnq) time.

Question 2: Sudoku
------------------

This question is inspired by The Prime Minister of Singapore, 
Lee Hsien Loong, who once wrote a sudoku solver in C++:

https://www.facebook.com/leehsienloong/photos/a.344710778924968.83425.125845680811480/905828379479869/?type=1&theater

In the game of sudoku, we are given a 9x9 grid, with some
of the cells filled with numbers 1 to 9.  We must fill up
the rest of the cells with 1 to 9, such that no number
repeats itself in each row, in each column, and in each
of the nine 3×3 subgrids.

Write a program, `sudoku.c`, that reads in a sudoku
puzzle, and search for a solution to the puzzle, using
the following algorithm:

- Start from the top left, and scan left to right, top
  to bottom.

- If an empty cell is encountered, try to fill it up with
a digit, starting
  with 1, 2, .. until 9.  For each digit we try, check if
  it is possible to find a solution, and if so, solve the
  updated puzzle recursively.

- If a solution is found, print the solution and stop
searching.  Otherwise,
  (backtrack and) try a different digit, until either we
  have tried all digits or a solution is found.

The input to the program consists of 9 lines, 9 characters
in each line, representing the puzzle.  The input
contains only the digits 1 to 9 and the `.` character,
which represents the empty cell.

The output contains the steps of the search, printed with
`print_sudoku` method provided.  At the end of the program,
either the solution is printed or the string "no solution"
if the sudoku cannot be solved.

You can try to run the program ~cs1010/sudoku to see the
animation of how the solution is expected to work.
