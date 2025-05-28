#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MARKED 1
#define GRID_SIZE (256 * 256)

void trace(char **maze, int *marker, int rows, int cols, int row, int col,
           int *area, int *perim) {
  char sym = maze[row][col];
  int idx = row * rows + col;
  stack_init();
  stack_push(idx);
  int left, right, top, bottom, r, c;

  *area = 0;
  *perim = 0;
  while (stack_size()) {
    idx = stack_pop();

    if (marker[idx] == MARKED) {
      continue;
    }

    *area += 1;
    r = idx / rows;
    c = idx % rows;

    // mark the cell counted
    marker[idx] = MARKED;

    // check top
    if (r > 0) {
      if (maze[r - 1][c] == sym) {
        if (marker[idx - rows] != MARKED) {
          stack_push(idx - rows);
        }
      } else {
        *perim += 1;
      }
    } else {
      *perim += 1;
    }

    // check bottom
    if (r < rows - 1) {
      if (maze[r + 1][c] == sym) {
        if (marker[idx + rows] != MARKED) {
          stack_push(idx + rows);
        }
      } else {
        *perim += 1;
      }
    } else {
      *perim += 1;
    }

    // check left
    if (c > 0) {
      if (maze[r][c - 1] == sym) {
        if (marker[idx - 1] != MARKED) {
          stack_push(idx - 1);
        }
      } else {
        *perim += 1;
      }
    } else {
      *perim += 1;
    }

    // check right
    if (c < cols - 1) {
      if (maze[r][c + 1] == sym) {
        if (marker[idx + 1] != MARKED) {
          stack_push(idx + 1);
        }
      } else {
        *perim += 1;
      }
    } else {
      *perim += 1;
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 1) {
    exit(1);
  }

  char *file_path = argv[1];
  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    exit(1);
  }

  int rows;
  int cols;
  char **maze = read_maze(file, &rows, &cols);
  fclose(file);

  // keeps track of counted cells
  int *marker = calloc(rows * cols, sizeof(int));
  int area;
  int perimeter;
  long sum = 0;
  int idx;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      idx = row * rows + col;
      if (marker[idx] == MARKED) {
        continue;
      }
      trace(maze, marker, rows, cols, row, col, &area, &perimeter);
      /* printf("ch: %c ar: %d pm: %d\n", maze[row][col], area, perimeter); */
      sum += area * perimeter;
    }
  }

  printf("sum is: %ld\n", sum);

  for (int i = 0; i < rows; i++) {
    free(maze[i]);
  }

  free(maze);
  free(marker);
}
