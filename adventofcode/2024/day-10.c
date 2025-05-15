#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE (256 * 256)

int trace(char **maze, int rows, int cols, int row, int col) {
  int queue[GRID_SIZE];
  int nines[GRID_SIZE];
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
  int score = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    score += nines[i];
  }

  return score;
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

  char **maze = malloc(256 * sizeof(*maze));
  int rows = 0;
  do {
    maze[rows] = malloc(256 * sizeof(**maze));
  } while (fgets(maze[rows++], 256 * sizeof(**maze), file));
  rows--;
  int cols = (int)strlen(maze[0]) - 1; // strip newline

  int total_score = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (maze[i][j] == '0') {
        total_score += trace(maze, rows, cols, i, j);
      }
    }
  }

  printf("score: %d\n", total_score);

  for (int i = 0; i < rows; i++) {
    free(maze[i]);
  }

  free(maze);
}
