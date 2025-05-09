#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rows = 130;
static int cols = 130;

int move(int **maze, int *curr_row, int *curr_col, int *direction) {
    int next_row = *curr_row;
    int next_col = *curr_col;

    switch (*direction) {
        case 0: //  up
            next_row = (*curr_row) - 1;
            break;
        case 1: //  right
            next_col = (*curr_col) + 1;
            break;
        case 2: //  down
            next_row = (*curr_row) + 1;
            break;
        case 3: //  left
            next_col = (*curr_col) - 1;
            break;
    }

    if (next_row < 0 || next_row > rows - 1 ||
        next_col < 0 || next_col > cols - 1) {
        return 0; // exited maze
    } else if (maze[next_row][next_col] == 1) {
        // objstacle, change direction 90%
        *direction = (*direction + 1) % 4;
    } else {
        *curr_row = next_row;
        *curr_col = next_col;
    }
    return 1;
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

  char *str;
  static int **maze;

  char line[256];

  maze = (int **) malloc(rows * sizeof(int *));
  for (int i = 0; i < cols; i++) {
    maze[i] = (int *) malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
        maze[i][j] = 0; // no obstacle
    }
  }

  int curr_row = 0;
  int curr_col = 0;

  int row =  0;
  while (fgets(line, sizeof(line), file)) {
    if (strncmp("\n", line, 1) == 0) {
      break;
    }

    /* printf("%d: %s\n", row, line); */
    for (int col = 0; col < cols; col++) {
        if (line[col] == '#') {
            maze[row][col] = 1;
        } else if (line[col] == '^') {
            curr_row = row;
            curr_col = col;
        }
    }

    row++;
  }

  /* printf("row: %d, col: %d\n",  curr_row,  curr_col); */

  // patrol
  int direction = 0; // 0 - up, 1 - right, 2 - down, 3 - left

  maze[curr_row][curr_col] = 2; // mark as visited
  /* printf("row: %d, col: %d\n", curr_row, curr_col); */
  while(move(maze, &curr_row, &curr_col, &direction)) {
      maze[curr_row][curr_col] = 2; // mark as visited
      /* printf("row: %d, col: %d, dir: %d\n", curr_row, curr_col, direction); */
  }

  int visited_pos = 0;
  for (int i = 0; i < rows; i++ ) {
      for(int j = 0; j < cols; j++) {
          if (maze[i][j] == 2) {
              visited_pos++;
          }
      }
  }

  printf("visited unique positions: %d\n", visited_pos);
}
