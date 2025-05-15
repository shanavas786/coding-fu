#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 1) {
    exit(1);
  }

  char *file_path = argv[1];
  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    exit(1);
  }

  int num_antinodes = 0;
  int num_antinodes2 = 0;
  int rows;
  int cols;
  char **maze = read_maze(file, &rows, &cols);
  printf("rows: %d, cols: %d\n", rows, cols);

  int **antinodes = (int **)malloc(rows * sizeof(*antinodes));
  int **antinodes2 = (int **)malloc(rows * sizeof(*antinodes));
  for (int i = 0; i < rows; i++) {
    antinodes[i] = (int *)malloc(cols * sizeof(int));
    antinodes2[i] = (int *)malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      antinodes[i][j] = 0;
      antinodes2[i][j] = 0;
    }
  }

  int row_diff;
  int col_diff;
  int a_row;
  int a_col;
  int b_row;
  int b_col;

  for (int row1 = 0; row1 < rows; row1++) {
    for (int col1 = 0; col1 < cols; col1++) {
      if (maze[row1][col1] == '.') {
        continue;
      }

      char symbol = maze[row1][col1];
      for (int row2 = row1; row2 < rows; row2++) {
        for (int col2 = 0; col2 < cols; col2++) {
          if (maze[row2][col2] != symbol || (row2 == row1 && col1 <= col2)) {
            continue;
          }

          antinodes2[row1][col1] = 1;
          antinodes2[row2][col2] = 1;

          row_diff = row2 - row1;
          col_diff = col2 - col1;

          a_row = row1 - row_diff;
          a_col = col1 - col_diff;
          b_row = row2 + row_diff;
          b_col = col2 + col_diff;

          if (a_row >= 0 && a_row < rows && a_col >= 0 && a_col < cols) {
            antinodes[a_row][a_col] = 1;
          }
          if (b_row >= 0 && b_row < rows && b_col >= 0 && b_col < cols) {
            antinodes[b_row][b_col] = 1;
          }

          while (a_row >= 0 && a_row < rows && a_col >= 0 && a_col < cols) {
            antinodes2[a_row][a_col] = 1;
            a_row = a_row - row_diff;
            a_col = a_col - col_diff;
          }
          while (b_row >= 0 && b_row < rows && b_col >= 0 && b_col < cols) {
            antinodes2[b_row][b_col] = 1;
            b_row = b_row + row_diff;
            b_col = b_col + col_diff;
          }
        }
      }
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      num_antinodes += antinodes[i][j];
      num_antinodes2 += antinodes2[i][j];
    }
  }

  for (int i = 0; i < rows; i++) {
    free(maze[i]);
    free(antinodes[i]);
    free(antinodes2[i]);
  }

  free(maze);
  free(antinodes);
  free(antinodes2);

  printf("Number of antinodes: %d\n", num_antinodes);
  printf("Number of antinodes2: %d\n", num_antinodes2);
  return 0;
}
