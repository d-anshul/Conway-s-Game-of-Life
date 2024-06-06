#include "life.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
You are required to implement the rules of Conway’s Game of Life, with the
change that all cells not displayed in the required viewport are always
considered dead. Your program must compute the rules of the Game of Life on a
grid that is 80 cells wide by 24 cells high, assuming that all cells outside of
this grid are dead. These constants are defined in the given file life.h as
GRIDX anad GRIDY, respectively. The rules of Life are simple, and applied to
every cell in the grid in the exact same fashion. Life proceeds in generations,
where the state of the cells in generation G entirely determines the state of
the cells in generation G + 1. The state of each cell in generation G + 1 is
determined by the state of its eight neighboring cells in generation G;
specifically, the number of those cells that are alive or dead. The neighbors of
a cell are the cells immediately to its left, right, above, below, and on the
four diagonals between those cells. The rules for a cell c are as follows: • If
c is alive and has fewer than 2 live neighbors, it dies. • If c is alive and has
more than 3 live neighbors, it dies. • If c is alive and has exactly 2 or 3 live
neighbors, it remains alive. • If c is dead and has exactly 3 live neighbors, it
becomes alive.

The neighbors of the cell marked in the center of this grid are the cells marked
in gray:
X
Your implementation will use the character 'X' to represent a live cell, and the
space character ' ' to rep- resent a dead cell. There are two constants defined
in the given code, LIVE and DEAD, for this purpose. Your implementation must
accept two command line arguments, a filename and a generation number. The
filename is a file containing a starting state to be passed to the given
function parse_life() (documented else- where in this handout), which will
produce a grid with the initial state of the game, and the generation number is
the generation which your program should output. Generation 0 is the starting
state of the game as parsed by parse_life(). Upon reaching the stated
generation, your program must output the state of the grid, using exactly the
format described here. Any difference in format, including extra or missing
whitespace, will result in reduced credit on this assignment. The grid should be
output as follows: • Every row of the GRIDY rows in the grid must be output as a
single line of text ending in a newline. • Every cell of the GRIDX cells in a
row of the grid must be output as a single character, either an ASCII space for
a dead cell or an ASCII X for a live cell. Your output will therefore be exactly
24 lines of exactly 80 characters each. Any deviation from this output is
incorrect. In particular, extra whitespace at the beginnings or ends of lines,
for example, will look like extra dead cells. Any invocation with fewer than one
argument or more than two arguments should print an error message and exit
(e.g., return from main()) with a non-zero exit status, with one exception: you
may accept extra argu- ments beginning with a dash (-) character to enable
different behaviors in your program for your own use in testing.
*/

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    printf("Usage: %s <filename> <generation>\n", argv[0]);
    return -1;
  }

  /*
You are required to implement the rules of Conway’s Game of Life, with the
change that all cells not displayed in the required viewport are always
considered dead. Your program must compute the rules of the Game of Life on a
grid that is 80 cells wide by 24 cells high, assuming that all cells outside of
this grid are dead. These constants are defined in the given file life.h as
GRIDX anad GRIDY, respectively. The rules of Life are simple, and applied to
every cell in the grid in the exact same fashion. Life proceeds in generations,
where the state of the cells in generation G entirely determines the state of
the cells in generation G + 1. The state of each cell in generation G + 1 is
determined by the state of its eight neighboring cells in generation G;
specifically, the number of those cells that are alive or dead. The neighbors of
a cell are the cells immediately to its left, right, above, below, and on the
four diagonals between those cells. The rules for a cell c are as follows: • If
c is alive and has fewer than 2 live neighbors, it dies. • If c is alive and has
more than 3 live neighbors, it dies. • If c is alive and has exactly 2 or 3 live
neighbors, it remains alive. • If c is dead and has exactly 3 live neighbors, it
becomes alive.

The neighbors of the cell marked in the center of this grid are the cells marked
in gray:
X
Your implementation will use the character 'X' to represent a live cell, and the
space character ' ' to rep- resent a dead cell. There are two constants defined
in the given code, LIVE and DEAD, for this purpose. Your implementation must
accept two command line arguments, a filename and a generation number. The
filename is a file containing a starting state to be passed to the given
function parse_life() (documented else- where in this handout), which will
produce a grid with the initial state of the game, and the generation number is
the generation which your program should output. Generation 0 is the starting
state of the game as parsed by parse_life(). Upon reaching the stated
generation, your program must output the state of the grid, using exactly the
format described here. Any difference in format, including extra or missing
whitespace, will result in reduced credit on this assignment. The grid should be
output as follows: • Every row of the GRIDY rows in the grid must be output as a
single line of text ending in a newline. • Every cell of the GRIDX cells in a
row of the grid must be output as a single character, either an ASCII space for
a dead cell or an ASCII X for a live cell. Your output will therefore be exactly
24 lines of exactly 80 characters each. Any deviation from this output is
incorrect. In particular, extra whitespace at the beginnings or ends of lines,
for example, will look like extra dead cells. Any invocation with fewer than one
argument or more than two arguments should print an error message and exit
(e.g., return from main()) with a non-zero exit status, with one exception: you
may accept extra argu- ments beginning with a dash (-) character to enable
different behaviors in your program for your own use in testing.
*/

  int num = atoi(argv[2]);
  char **current_generation = parse_life(argv[1]);
  char **next_generation = (char **)malloc(sizeof(char *) * GRIDY);

  for (int i = 0; i < GRIDY; i++) {
    next_generation[i] = (char *)malloc(sizeof(char) * GRIDX);
  }

  // Define arrays for neighbor coordinates
  int row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int col[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int gen = 0; gen < num; gen++) {

    for (int y = 0; y < GRIDY; y++) {
      for (int x = 0; x < GRIDX; x++) {
        int count = 0;

        for (int j = 0; j < 8; j++) {
          int neighbor_row = y + row[j];
          int neighbor_col = x + col[j];

          if (neighbor_row >= 0 && neighbor_row < GRIDY && neighbor_col >= 0 &&
              neighbor_col < GRIDX) {
            if (current_generation[neighbor_row][neighbor_col] == LIVE) {
              count++;
            }
          }
        }

        if (current_generation[y][x] == LIVE) {
          if (count < 2 || count > 3) {
            next_generation[y][x] = DEAD;
          } else {
            next_generation[y][x] = LIVE;
          }
        } else {
          if (count == 3) {
            next_generation[y][x] = LIVE;
          } else {
            next_generation[y][x] = DEAD;
          }
        }
      }
    }
    /*
    You are required to implement the rules of Conway’s Game of Life, with the
    change that all cells not displayed in the required viewport are always
    considered dead. Your program must compute the rules of the Game of Life on
    a grid that is 80 cells wide by 24 cells high, assuming that all cells
    outside of this grid are dead. These constants are defined in the given file
    life.h as GRIDX anad GRIDY, respectively. The rules of Life are simple, and
    applied to every cell in the grid in the exact same fashion. Life proceeds
    in generations, where the state of the cells in generation G entirely
    determines the state of the cells in generation G + 1. The state of each
    cell in generation G + 1 is determined by the state of its eight neighboring
    cells in generation G; specifically, the number of those cells that are
    alive or dead. The neighbors of a cell are the cells immediately to its
    left, right, above, below, and on the four diagonals between those cells.
    The rules for a cell c are as follows: • If c is alive and has fewer than 2
    live neighbors, it dies. • If c is alive and has more than 3 live neighbors,
    it dies. • If c is alive and has exactly 2 or 3 live neighbors, it remains
    alive. • If c is dead and has exactly 3 live neighbors, it becomes alive.

    The neighbors of the cell marked in the center of this grid are the cells
    marked in gray:
    X
    Your implementation will use the character 'X' to represent a live cell, and
    the space character ' ' to rep- resent a dead cell. There are two constants
    defined in the given code, LIVE and DEAD, for this purpose. Your
    implementation must accept two command line arguments, a filename and a
    generation number. The filename is a file containing a starting state to be
    passed to the given function parse_life() (documented else- where in this
    handout), which will produce a grid with the initial state of the game, and
    the generation number is the generation which your program should output.
    Generation 0 is the starting state of the game as parsed by parse_life().
    Upon reaching the stated generation, your program must output the state of
    the grid, using exactly the format described here. Any difference in format,
    including extra or missing whitespace, will result in reduced credit on this
    assignment. The grid should be output as follows: • Every row of the GRIDY
    rows in the grid must be output as a single line of text ending in a
    newline. • Every cell of the GRIDX cells in a row of the grid must be output
    as a single character, either an ASCII space for a dead cell or an ASCII X
    for a live cell. Your output will therefore be exactly 24 lines of exactly
    80 characters each. Any deviation from this output is incorrect. In
    particular, extra whitespace at the beginnings or ends of lines, for
    example, will look like extra dead cells. Any invocation with fewer than one
    argument or more than two arguments should print an error message and exit
    (e.g., return from main()) with a non-zero exit status, with one exception:
    you may accept extra argu- ments beginning with a dash (-) character to
    enable different behaviors in your program for your own use in testing.
    */

    char **temp = current_generation;
    current_generation = next_generation;
    next_generation = temp;
  }

  for (int y = 0; y < GRIDY; y++) {
    for (int x = 0; x < GRIDX; x++) {
      putchar(current_generation[y][x]);
    }
    putchar('\n');
  }

  /*
  You are required to implement the rules of Conway’s Game of Life, with the
  change that all cells not displayed in the required viewport are always
  considered dead. Your program must compute the rules of the Game of Life on a
  grid that is 80 cells wide by 24 cells high, assuming that all cells outside
  of this grid are dead. These constants are defined in the given file life.h as
  GRIDX anad GRIDY, respectively. The rules of Life are simple, and applied to
  every cell in the grid in the exact same fashion. Life proceeds in
  generations, where the state of the cells in generation G entirely determines
  the state of the cells in generation G + 1. The state of each cell in
  generation G + 1 is determined by the state of its eight neighboring cells in
  generation G; specifically, the number of those cells that are alive or dead.
  The neighbors of a cell are the cells immediately to its left, right, above,
  below, and on the four diagonals between those cells. The rules for a cell c
  are as follows:
  • If c is alive and has fewer than 2 live neighbors, it dies.
  • If c is alive and has more than 3 live neighbors, it dies.
  • If c is alive and has exactly 2 or 3 live neighbors, it remains alive.
  • If c is dead and has exactly 3 live neighbors, it becomes alive.

  The neighbors of the cell marked in the center of this grid are the cells
  marked in gray:
  X
  Your implementation will use the character 'X' to represent a live cell, and
  the space character ' ' to rep- resent a dead cell. There are two constants
  defined in the given code, LIVE and DEAD, for this purpose. Your
  implementation must accept two command line arguments, a filename and a
  generation number. The filename is a file containing a starting state to be
  passed to the given function parse_life() (documented else- where in this
  handout), which will produce a grid with the initial state of the game, and
  the generation number is the generation which your program should output.
  Generation 0 is the starting state of the game as parsed by parse_life(). Upon
  reaching the stated generation, your program must output the state of the
  grid, using exactly the format described here. Any difference in format,
  including extra or missing whitespace, will result in reduced credit on this
  assignment. The grid should be output as follows: • Every row of the GRIDY
  rows in the grid must be output as a single line of text ending in a newline.
  • Every cell of the GRIDX cells in a row of the grid must be output as a
  single character, either an ASCII space for a dead cell or an ASCII X for a
  live cell. Your output will therefore be exactly 24 lines of exactly 80
  characters each. Any deviation from this output is incorrect. In particular,
  extra whitespace at the beginnings or ends of lines, for example, will look
  like extra dead cells. Any invocation with fewer than one argument or more
  than two arguments should print an error message and exit (e.g., return from
  main()) with a non-zero exit status, with one exception: you may accept extra
  argu- ments beginning with a dash (-) character to enable different behaviors
  in your program for your own use in testing.
  */

  for (int i = 0; i < GRIDY; i++) {
    free(current_generation[i]);
    free(next_generation[i]);
  }
  free(current_generation);
  free(next_generation);

  return 0;
}
/*
You are required to implement the rules of Conway’s Game of Life, with the
change that all cells not displayed in the required viewport are always
considered dead. Your program must compute the rules of the Game of Life on a
grid that is 80 cells wide by 24 cells high, assuming that all cells outside of
this grid are dead. These constants are defined in the given file life.h as
GRIDX anad GRIDY, respectively. The rules of Life are simple, and applied to
every cell in the grid in the exact same fashion. Life proceeds in generations,
where the state of the cells in generation G entirely determines the state of
the cells in generation G + 1. The state of each cell in generation G + 1 is
determined by the state of its eight neighboring cells in generation G;
specifically, the number of those cells that are alive or dead. The neighbors of
a cell are the cells immediately to its left, right, above, below, and on the
four diagonals between those cells. The rules for a cell c are as follows: • If
c is alive and has fewer than 2 live neighbors, it dies. • If c is alive and has
more than 3 live neighbors, it dies. • If c is alive and has exactly 2 or 3 live
neighbors, it remains alive. • If c is dead and has exactly 3 live neighbors, it
becomes alive.

The neighbors of the cell marked in the center of this grid are the cells marked
in gray:
X
Your implementation will use the character 'X' to represent a live cell, and the
space character ' ' to rep- resent a dead cell. There are two constants defined
in the given code, LIVE and DEAD, for this purpose. Your implementation must
accept two command line arguments, a filename and a generation number. The
filename is a file containing a starting state to be passed to the given
function parse_life() (documented else- where in this handout), which will
produce a grid with the initial state of the game, and the generation number is
the generation which your program should output. Generation 0 is the starting
state of the game as parsed by parse_life(). Upon reaching the stated
generation, your program must output the state of the grid, using exactly the
format described here. Any difference in format, including extra or missing
whitespace, will result in reduced credit on this assignment. The grid should be
output as follows: • Every row of the GRIDY rows in the grid must be output as a
single line of text ending in a newline. • Every cell of the GRIDX cells in a
row of the grid must be output as a single character, either an ASCII space for
a dead cell or an ASCII X for a live cell. Your output will therefore be exactly
24 lines of exactly 80 characters each. Any deviation from this output is
incorrect. In particular, extra whitespace at the beginnings or ends of lines,
for example, will look like extra dead cells. Any invocation with fewer than one
argument or more than two arguments should print an error message and exit
(e.g., return from main()) with a non-zero exit status, with one exception: you
may accept extra argu- ments beginning with a dash (-) character to enable
different behaviors in your program for your own use in testing.
*/
