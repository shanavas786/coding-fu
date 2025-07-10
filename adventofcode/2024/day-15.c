#include "libs/utils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 128

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

int move_box_right2(char grid[][GRID_SIZE], int rows, int cols, int bx,
                    int by) {
    for (int i = bx; i < cols; i++) {
        if (grid[by][i] == '#') {
            break;
        } else if (grid[by][i] == '.') {
            for (int j = i; j > bx; j--) {
                grid[by][j] = grid[by][j - 1];
            }
            grid[by][bx] = '.';
            return 1;
        }
    }

    return 0;
}

int move_box_left2(char grid[][GRID_SIZE], int rows, int cols, int bx, int by) {
    for (int i = bx; i > 0; i--) {
        if (grid[by][i] == '#') {
            break;
        } else if (grid[by][i] == '.') {
            for (int j = i; j < bx; j++) {
                grid[by][j] = grid[by][j + 1];
            }

            grid[by][bx] = '.';
            return 1;
        }
    }
    return 0;
}

int can_move_box_up(char grid[][GRID_SIZE], int rows, int cols, int bx,
                    int by) {
    int c1 = bx;
    int c2;
    if (grid[by][bx] == '[') {
        c2 = bx + 1;
    } else {
        c2 = bx - 1;
    }

    if (grid[by - 1][c1] == '#' || grid[by - 1][c2] == '#') {
        return 0;
    }

    if (grid[by - 1][c1] == '.' && grid[by - 1][c2] == '.') {
        return 1;
    }

    if (grid[by - 1][c1] != '.' && grid[by - 1][c2] != '.') {
        // above both c1 and c2 are objects
        if (grid[by - 1][c1] == grid[by][c1]) {
            // objects are rightly alighned
            return can_move_box_up(grid, rows, cols, c1, by - 1);
        } else {
            return can_move_box_up(grid, rows, cols, c1, by - 1) &&
                   can_move_box_up(grid, rows, cols, c2, by - 1);
        }
    }

    // one of them is . and other is an object
    if (grid[by - 1][c1] == '.') {
        // above c2 is an object
        return can_move_box_up(grid, rows, cols, c2, by - 1);
    }

    // above c1 is an object
    return can_move_box_up(grid, rows, cols, c1, by - 1);
}

void do_move_box_up2(char grid[][GRID_SIZE], int rows, int cols, int bx,
                     int by) {
    int c1 = bx;
    int c2;
    if (grid[by][bx] == '[') {
        c2 = bx + 1;
    } else {
        c2 = bx - 1;
    }

    if (grid[by - 1][c1] == '.' && grid[by - 1][c2] == '.') {
        // do nothing
    } else if (grid[by - 1][c1] == '.') {
        // move c2
        do_move_box_up2(grid, rows, cols, c2, by - 1);
    } else if (grid[by - 1][c2] == '.') {
        // move c1
        do_move_box_up2(grid, rows, cols, c1, by - 1);
    } else if (grid[by - 1][c2] == grid[by][c2]) {
        // boxes aligned
        do_move_box_up2(grid, rows, cols, c2, by - 1);
    } else {
        // move both boxes
        do_move_box_up2(grid, rows, cols, c1, by - 1);
        do_move_box_up2(grid, rows, cols, c2, by - 1);
    }

    grid[by - 1][c1] = grid[by][c1];
    grid[by - 1][c2] = grid[by][c2];
    grid[by][c1] = '.';
    grid[by][c2] = '.';
}

int move_box_up2(char grid[][GRID_SIZE], int rows, int cols, int bx, int by) {
    if (grid[by][bx] == '#') {
        return 0;
    }

    // push a box

    if (can_move_box_up(grid, rows, cols, bx, by)) {
        do_move_box_up2(grid, rows, cols, bx, by);
        return 1;
    }

    return 0;
}

int can_move_box_down(char grid[][GRID_SIZE], int rows, int cols, int bx,
                      int by) {
    int c1 = bx;
    int c2;
    if (grid[by][bx] == '[') {
        c2 = bx + 1;
    } else {
        c2 = bx - 1;
    }

    if (grid[by + 1][c1] == '#' || grid[by + 1][c2] == '#') {
        return 0;
    }

    if (grid[by + 1][c1] == '.' && grid[by + 1][c2] == '.') {
        return 1;
    }

    if (grid[by + 1][c1] != '.' && grid[by + 1][c2] != '.') {
        // above both c1 and c2 are objects
        if (grid[by + 1][c1] == grid[by][c1]) {
            // objects are rightly alighned
            return can_move_box_down(grid, rows, cols, c1, by + 1);
        } else {
            return can_move_box_down(grid, rows, cols, c1, by + 1) &&
                   can_move_box_down(grid, rows, cols, c2, by + 1);
        }
    }

    // one of them is . and other is an object
    if (grid[by + 1][c1] == '.') {
        // below c2 is an object
        return can_move_box_down(grid, rows, cols, c2, by + 1);
    }

    // below c1 is an object
    return can_move_box_down(grid, rows, cols, c1, by + 1);
}

void do_move_box_down2(char grid[][GRID_SIZE], int rows, int cols, int bx,
                       int by) {
    int c1 = bx;
    int c2;
    if (grid[by][bx] == '[') {
        c2 = bx + 1;
    } else {
        c2 = bx - 1;
    }

    if (grid[by + 1][c1] == '.' && grid[by + 1][c2] == '.') {
        // do nothing
    } else if (grid[by + 1][c1] == '.') {
        // move c2
        do_move_box_down2(grid, rows, cols, c2, by + 1);
    } else if (grid[by + 1][c2] == '.') {
        // move c1
        do_move_box_down2(grid, rows, cols, c1, by + 1);
    } else if (grid[by + 1][c2] == grid[by][c2]) {
        // boxes aligned
        do_move_box_down2(grid, rows, cols, c2, by + 1);
    } else {
        // move both boxes
        do_move_box_down2(grid, rows, cols, c1, by + 1);
        do_move_box_down2(grid, rows, cols, c2, by + 1);
    }

    grid[by + 1][c1] = grid[by][c1];
    grid[by + 1][c2] = grid[by][c2];
    grid[by][c1] = '.';
    grid[by][c2] = '.';
}

int move_box_down2(char grid[][GRID_SIZE], int rows, int cols, int bx, int by) {
    if (grid[by][bx] == '#') {
        return 0;
    }

    // push a box
    if (can_move_box_down(grid, rows, cols, bx, by)) {
        do_move_box_down2(grid, rows, cols, bx, by);
        return 1;
    }

    return 0;
}

int move2(char grid[][GRID_SIZE], int rows, int cols, int *x, int *y,
          char sym) {

    int rx = *x;
    int ry = *y;

    int moved = 0;

    switch (sym) {
    case '>':
        // move right
        if (grid[ry][rx + 1] == '.' ||
            move_box_right2(grid, rows, cols, rx + 1, ry)) {
            grid[ry][rx + 1] = '@';
            grid[ry][rx] = '.';
            moved = 1;
            *x += 1;
        }
        break;
    case '<':
        // move left
        if (grid[ry][rx - 1] == '.' ||
            move_box_left2(grid, rows, cols, rx - 1, ry)) {
            grid[ry][rx - 1] = '@';
            grid[ry][rx] = '.';
            moved = 1;
            *x -= 1;
        }

        break;
    case 'v':
        // move down
        if (grid[ry + 1][rx] == '.' ||
            move_box_down2(grid, rows, cols, rx, ry + 1)) {
            grid[ry + 1][rx] = '@';
            grid[ry][rx] = '.';
            moved = 1;
            *y += 1;
        }

        break;
    case '^':
        // move up
        if (grid[ry - 1][rx] == '.' ||
            move_box_up2(grid, rows, cols, rx, ry - 1)) {
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
    char grid2[GRID_SIZE][GRID_SIZE] = {0};
    char line[1024];

    // read maze
    int rows = 0;
    int cols = 0;
    int rx, ry;   // robot position
    int rx2, ry2; // robot position

    char *r;
    while (fgets(grid[rows], sizeof(grid[rows]), file)) {
        if (strlen(grid[rows]) == 1) {
            cols = strlen(grid[rows - 1]) - 1;
            break;
        }

        for (int i = 0; i < strlen(grid[rows]); i++) {
            switch (grid[rows][i]) {
            case '#':
                grid2[rows][i * 2] = '#';
                grid2[rows][i * 2 + 1] = '#';
                break;
            case 'O':
                grid2[rows][i * 2] = '[';
                grid2[rows][i * 2 + 1] = ']';
                break;
            case '.':
                grid2[rows][i * 2] = '.';
                grid2[rows][i * 2 + 1] = '.';
                break;
            case '@':
                ry = rows;
                rx = i;
                ry2 = rows;
                rx2 = i * 2;
                grid2[rows][i * 2] = '@';
                grid2[rows][i * 2 + 1] = '.';
                break;
            default:
                break;
            }
        }

        rows++;
    }

    int rows2 = rows;
    int cols2 = cols * 2;

    printf("r: %d, c: %d, rx: %d, ry: %d\n", rows, cols, rx, ry);
    printf("r2: %d, c2: %d, rx2: %d, ry2: %d\n", rows2, cols2, rx2, ry2);
    for (int i = 0; i < rows2; i++) {
        printf("%s\n", grid2[i]);
    }

    char ch;
    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; i < strlen(line); i++) {
            ch = line[i];
            move(grid, rows, cols, &rx, &ry, ch);
            move2(grid2, rows2, cols2, &rx2, &ry2, ch);

            /* printf("---move %c-----\n", ch); */
            /* for (int k = 0; k < rows2; k++) { */
            /*     printf("%s\n", grid2[k]); */
            /* } */

            /* getc(stdin); */
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

    long score2 = 0;
    for (int i = 0; i < rows2; i++) {
        printf("%s\n", grid2[i]);
        for (int j = 0; j < cols2; j++) {
            if (grid2[i][j] == '[') {
                score2 += 100 * i + j;
            }
        }
    }

    printf("sum of GPS: %ld\n", score);
    printf("sum of GPS2: %ld\n", score2);

    fclose(file);
}
