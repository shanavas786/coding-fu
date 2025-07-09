#include "libs/utils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 64

int move_box_right(char grid[][GRID_SIZE], int rows, int cols, int bx, int by) {
    for (int i = bx; i < cols; i++) {
        if (grid[by][i] == '#') {
            break;
        } else if (grid[by][i] == '.') {
            // swap
            grid[by][i] = 'O';
            grid[by][bx] = '.';
            return 1;
        }
    }

    return 0;
}

int move_box_left(char grid[][GRID_SIZE], int rows, int cols, int bx, int by) {
    for (int i = bx; i > 0; i--) {
        if (grid[by][i] == '#') {
            break;
        } else if (grid[by][i] == '.') {
            // swap
            grid[by][i] = 'O';
            grid[by][bx] = '.';
            return 1;
        }
    }
    return 0;
}

int move_box_up(char grid[][GRID_SIZE], int rows, int cols, int bx, int by) {
    for (int i = by; i > 0; i--) {
        if (grid[i][bx] == '#') {
            break;
        } else if (grid[i][bx] == '.') {
            // swap
            grid[i][bx] = 'O';
            grid[by][bx] = '.';
            return 1;
        }
    }
    return 0;
}

int move_box_down(char grid[][GRID_SIZE], int rows, int cols, int bx, int by) {
    for (int i = by; i < rows; i++) {
        if (grid[i][bx] == '#') {
            break;
        } else if (grid[i][bx] == '.') {
            // swap
            grid[i][bx] = 'O';
            grid[by][bx] = '.';
            return 1;
        }
    }
    return 0;
}

int move(char grid[][GRID_SIZE], int rows, int cols, int *x, int *y, char sym) {

    int rx = *x;
    int ry = *y;

    int moved = 0;

    switch (sym) {
    case '>':
        // move right
        if (grid[ry][rx + 1] == '.' ||
            move_box_right(grid, rows, cols, rx + 1, ry)) {
            grid[ry][rx + 1] = '@';
            grid[ry][rx] = '.';
            moved = 1;
            *x += 1;
        }
        break;
    case '<':
        // move left
        if (grid[ry][rx - 1] == '.' ||
            move_box_left(grid, rows, cols, rx - 1, ry)) {
            grid[ry][rx - 1] = '@';
            grid[ry][rx] = '.';
            moved = 1;
            *x -= 1;
        }

        break;
    case 'v':
        // move down
        if (grid[ry + 1][rx] == '.' ||
            move_box_down(grid, rows, cols, rx, ry + 1)) {
            grid[ry + 1][rx] = '@';
            grid[ry][rx] = '.';
            moved = 1;
            *y += 1;
        }

        break;
    case '^':
        // move up
        if (grid[ry - 1][rx] == '.' ||
            move_box_up(grid, rows, cols, rx, ry - 1)) {
            grid[ry - 1][rx] = '@';
            grid[ry][rx] = '.';
            moved = 1;
            *y -= 1;
        }
        break;
    default:
        break;
    }

    return moved;
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

    char grid[GRID_SIZE][GRID_SIZE] = {0};
    char line[1024];

    // read maze
    int rows = 0;
    int cols = 0;
    int rx, ry; // robot position

    char *r;
    while (fgets(grid[rows], sizeof(grid[rows]), file)) {
        if (strlen(grid[rows]) == 1) {
            cols = strlen(grid[rows - 1]) - 1;
            break;
        }

        if ((r = strchr(grid[rows], '@'))) {
            ry = rows;
            rx = r - grid[rows];
        }

        rows++;
    }

    printf("r: %d, c: %d, rx: %d, ry: %d\n", rows, cols, rx, ry);
    for (int i = 0; i < rows; i++) {
        printf("%s", grid[i]);
    }

    char ch;
    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; i < strlen(line); i++) {
            ch = line[i];
            (move(grid, rows, cols, &rx, &ry, ch));
        }
    }

    long score = 0;
    for (int i = 0; i < rows; i++) {
        printf("%s", grid[i]);
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'O') {
                score += 100 * i + j;
            }
        }
    }

    printf("sum of GPS: %ld", score);

    fclose(file);
}
