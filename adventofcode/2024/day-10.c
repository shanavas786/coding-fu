#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE (256 * 256)

void trace(char **maze, int rows, int cols, int row, int col, int *score,
           int *rating) {
  int queue[GRID_SIZE];
  int nines[GRID_SIZE];
  *rating = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    queue[i] = 0;
    nines[i] = 0;
  }

  int idx = row * rows + col + 1;
  int r, c;
  int ridx = 0;
  int widx = 0;
  queue[widx++] = idx;

  while (ridx <= widx) {
    idx = queue[ridx++];
    /* printf("%d, %d, %d\n", ridx, widx, idx); */

    r = (idx - 1) / rows;
    c = (idx - 1) % rows;
    if (maze[r][c] == '9') {
      nines[idx - 1] = 1;
      (*rating)++;
    }

    // left
    if (c > 0 && maze[r][c - 1] == (maze[r][c] + 1)) {
      queue[widx++] = idx - 1;
    }

    // right
    if (c + 1 < cols && maze[r][c + 1] == (maze[r][c] + 1)) {
      queue[widx++] = idx + 1;
    }

    // up
    if (r > 0 && maze[r - 1][c] == (maze[r][c] + 1)) {
      queue[widx++] = idx - rows;
    }

    // down
    if (r + 1 < rows && maze[r + 1][c] == (maze[r][c] + 1)) {
      queue[widx++] = idx + rows;
    }
  }
  *score = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    (*score) += nines[i];
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

  int total_score = 0;
  int total_rating = 0;
  int score;
  int rating;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (maze[i][j] == '0') {
        trace(maze, rows, cols, i, j, &score, &rating);
        total_score += score;
        total_rating += rating;
      }
    }
  }

  printf("score: %d\n", total_score);
  printf("rating: %d\n", total_rating);

  for (int i = 0; i < rows; i++) {
    free(maze[i]);
  }

  free(maze);
}
