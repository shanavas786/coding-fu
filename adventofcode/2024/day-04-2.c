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

  char *str;
  int rows = 140;
  int cols = 140;

  char line[256];

  char **grid = malloc(rows * sizeof(char *));

  int i = 0;
  while (fgets(line, sizeof(line), file)) {
    char *row = malloc((cols + 1) * sizeof(char));

    for (int j = 0; j < cols; j++) {
      row[j] = line[j];
    }
    row[cols] = '\0';
    grid[i] = row;
    i++;
  }

  int matches = 0;
  int xmatches = 0;
  // horizontal search
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {

      // horizontal
      if (cols - col >= 4) {
        // forward
        if (strncmp("XMAS", &(grid[row][col]), 4) == 0) {
          /* printf("hf %d,%d\n", row, col); */
          matches++;
        }
        // reverse
        if (strncmp("SAMX", &(grid[row][col]), 4) == 0) {
          /* printf("hb %d,%d\n", row, col); */
          matches++;
        }
      }

      if (rows - row >= 4) {
        // forward
        /* printf("vf %d,%d\n", row, col); */
        if (grid[row][col] == 'X' && grid[row + 1][col] == 'M' &&
            grid[row + 2][col] == 'A' && grid[row + 3][col] == 'S') {
          matches++;
        }
        // backward
        /* printf("vb %d,%d\n", row, col); */
        if (grid[row][col] == 'S' && grid[row + 1][col] == 'A' &&
            grid[row + 2][col] == 'M' && grid[row + 3][col] == 'X') {
          matches++;
        }
      }

      // diagnal
      // 4 rows left, 4 cols left
      if ((rows - row >= 4) && (cols - col >= 4)) {
        // top left to bottom right
        /* printf("df %d,%d\n", row, col); */
        if (grid[row][col] == 'X' && grid[row + 1][col + 1] == 'M' &&
            grid[row + 2][col + 2] == 'A' && grid[row + 3][col + 3] == 'S') {
          matches++;
        }

        if (grid[row][col] == 'S' && grid[row + 1][col + 1] == 'A' &&
            grid[row + 2][col + 2] == 'M' && grid[row + 3][col + 3] == 'X') {
          matches++;
        }

      }

      // botom left to top right
      if (row >= 3 && (cols - col >= 4)) {
        if (grid[row][col] == 'X' && grid[row - 1][col + 1] == 'M' &&
            grid[row - 2][col + 2] == 'A' && grid[row - 3][col + 3] == 'S') {
          matches++;
        }

        if (grid[row][col] == 'S' && grid[row - 1][col + 1] == 'A' &&
            grid[row - 2][col + 2] == 'M' && grid[row - 3][col + 3] == 'X') {
          matches++;
        }
      }

      if (row > 0 && row < rows - 1 && col > 0 && col < cols - 1) {
        if (grid[row][col] == 'A') {
          if (grid[row - 1][col - 1] == 'M' && grid[row - 1][col + 1] == 'M' &&
              grid[row + 1][col - 1] == 'S' && grid[row + 1][col + 1] == 'S') {
            xmatches++;
          }

          if (grid[row - 1][col - 1] == 'M' && grid[row - 1][col + 1] == 'S' &&
              grid[row + 1][col - 1] == 'M' && grid[row + 1][col + 1] == 'S') {
            xmatches++;
          }

          if (grid[row - 1][col - 1] == 'S' && grid[row - 1][col + 1] == 'S' &&
              grid[row + 1][col - 1] == 'M' && grid[row + 1][col + 1] == 'M') {
            xmatches++;
          }

          if (grid[row - 1][col - 1] == 'S' && grid[row - 1][col + 1] == 'M' &&
              grid[row + 1][col - 1] == 'S' && grid[row + 1][col + 1] == 'M') {
            xmatches++;
          }
        }
      }
    }
  }

  for (int j = 0; j < rows; j++) {
    free(grid[j]);
  }

  free(grid);
  fclose(file);

  printf("XMAS matches: %d\n", matches);
  printf("X-MAS matches: %d\n", xmatches);
  return 0;
}
