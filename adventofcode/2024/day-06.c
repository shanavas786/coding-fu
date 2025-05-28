#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ROWS = 130;
static int COLS = 130;
static int OBSTACLE = -1;
static int EMPTY = -2;


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

    if (next_row < 0 || next_row > ROWS - 1 ||
        next_col < 0 || next_col > COLS - 1) {
        return 0; // exited maze
    } else if (maze[next_row][next_col] == OBSTACLE) {
        // objstacle, change direction 90%
        *direction = (*direction + 1) % 4;
    } else {
        *curr_row = next_row;
        *curr_col = next_col;
    }
    return 1;
}


int has_loop(int **maze, int init_row, int init_col) {
    int tor_row = init_row;
    int tor_col = init_col;
    int tor_dir = 0;
    int hare_row = init_row;
    int hare_col = init_col;
    int hare_dir = 0;

    while(1) {
        if (move(maze, &hare_row, &hare_col, &hare_dir) &&
            move(maze, &hare_row, &hare_col, &hare_dir) &&
            move(maze, &tor_row, &tor_col, &tor_dir)) {
            if (hare_row == tor_row && hare_col == tor_col && hare_dir == tor_dir) {
                return 1;
            }
        } else {
          break;
        }
    }
    return 0;
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
  static int **maze2;

  char line[256];

  maze = (int **) malloc(ROWS * sizeof(int *));
  maze2 = (int **) malloc(ROWS * sizeof(int *));
  for (int i = 0; i < COLS; i++) {
    maze[i] = (int *) malloc(COLS * sizeof(int));
    maze2[i] = (int *) malloc(COLS * sizeof(int));
    for (int j = 0; j < COLS; j++) {
        maze[i][j] = EMPTY; // no obstacle
        maze2[i][j] = EMPTY; // no obstacle
    }
  }

  int row =  0;
  int init_row = 0;
  int init_col = 0;
  while (fgets(line, sizeof(line), file)) {
    if (strncmp("\n", line, 1) == 0) {
      break;
    }

    /* printf("%d: %s\n", row, line); */
    for (int col = 0; col < COLS; col++) {
        if (line[col] == '#') {
            maze[row][col] = OBSTACLE;
            maze2[row][col] = OBSTACLE;
        } else if (line[col] == '^') {
            init_row = row;
            init_col = col;
        }
    }

    row++;
  }

  /* printf("row: %d, col: %d\n",  curr_row,  curr_col); */

  // patrol
  int direction = 0; // 0 - up, 1 - right, 2 - down, 3 - left
  int curr_row = init_row;
  int curr_col = init_col;

  maze[curr_row][curr_col] = direction; // mark as visited
  /* printf("row: %d, col: %d\n", curr_row, curr_col); */
  while(move(maze, &curr_row, &curr_col, &direction)) {
      maze[curr_row][curr_col] = direction; // mark as visited
      /* printf("row: %d, col: %d, dir: %d\n", curr_row, curr_col, direction); */
  }

  int visited_pos = 0;
  for (int i = 0; i < ROWS; i++ ) {
      for(int j = 0; j < COLS; j++) {
          if (maze[i][j] >= 0) {
              visited_pos++;
          }
      }
  }

  printf("visited unique positions: %d\n", visited_pos);

  int num_obstacles = 0;
  for (int i = 0; i < ROWS; i++ ) {
      for(int j = 0; j < COLS; j++) {
          // initial position, already has an objstacle or not visited
          if ((i == init_row && j == init_col) || maze[i][j] < 0) {
              continue;
          }

          /* printf("maze placed at row: %d, col: %d\n", i, j); */
          // place an obstacle
          maze2[i][j] = OBSTACLE;
          // check for loop
          if (has_loop(maze2, init_row, init_col)) {
              num_obstacles++;
          }

          // clear obstacle
          maze2[i][j] = EMPTY;
      }
  }

  printf("no. of new obstacles: %d\n", num_obstacles);

  // release
  for (int i = 0; i < ROWS; i++ ) {
      free(maze[i]);
      free(maze2[i]);
  }
  free(maze);
  free(maze2);
  fclose(file);
}
