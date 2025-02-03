#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/utils.h"

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
  // horizontal search
  for (int j = 0; j < rows; j++) {
      str = grid[j];
      // forward
      while ((str = strstr(str, "XMAS"))) {
          matches++;
          str++;
      }

      // reverse
      str = grid[j];
      while ((str = strstr(str, "SAMX"))) {
          matches++;
          str++;
      }

  }

  // vertical search
  char **tgrid = transpose(grid, rows, cols);
  for (int j = 0; j < cols; j++) {
      char *needle = tgrid[j];
      // forward
      while ((needle = strstr(needle, "XMAS"))) {
          matches++;
          needle++;
      }

      // reverse
      needle = tgrid[j];
      while ((needle = strstr(needle, "SAMX"))) {
          matches++;
          needle++;
      }
  }

  // diagnal bottom left to top right
  int row = 0;
  int col = 0;
  int p;
  int q;
  int idx;

  while (row < rows && col < cols) {
      char diag[256] = {'\0'};
      idx = 0;
      p = row;
      q = col;

      while (p >= 0 && q < cols) {
          diag[idx] = grid[p][q];
          idx++;
          p--;
          q++;
      }

      str = diag;
      // forward search
      while ((str = strstr(str, "XMAS"))) {
          matches++;
          str++;
      }

      // reverse
      str = diag;
      while ((str = strstr(str, "SAMX"))) {
          matches++;
          str++;
      }

      if (row < rows - 1) {
          row++;
      } else if (col < cols) {
          col++;
      }
  }


  // diagnal top left to bottom right
  row = rows - 1;
  col = 0;
  while (row >= 0 && col < cols) {
      char diag[256] = {'\0'};

      idx = 0;
      p = row;
      q = col;

      while (p < rows && q < cols) {
          diag[idx] = grid[p][q];
          idx++;
          p++;
          q++;
      }


      str = diag;
      // forward search
      while ((str = strstr(str, "XMAS"))) {
          matches++;
          str++;
      }

      // reverse
      str = diag;
      while ((str = strstr(str, "SAMX"))) {
          matches++;
          str++;
      }

      if (row > 0) {
          row--;
      } else if (col < cols) {
          col++;
      }
  }

  for (int j = 0; j < rows; j++) {
      free(grid[j]);
      free(tgrid[j]);
  }

  free(grid);
  free(tgrid);
  fclose(file);

  printf("matches: %d", matches);
  return 0;
}
