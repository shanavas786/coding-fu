#include "libs/utils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 71
#define MAX_BYTES 1024
#define CORRUPTED -1
#define UN_VISITED 0

int q[GRID_SIZE * GRID_SIZE][2] = {0};
int q_size = 0;
int q_widx = 0;
int q_ridx = 0;

void q_init() {
    q_size = 0;
    q_widx = 0;
    q_ridx = 0;
}

void q_push(int x, int y) {
    q[q_widx][0] = x;
    q[q_widx][1] = y;
    q_widx++;
    q_size++;
}

void q_pop(int *x, int *y) {
    *x = q[q_ridx][0];
    *y = q[q_ridx][1];
    q_ridx++;
    q_size--;
}

void reset_grid(int grid[][GRID_SIZE]) {
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            if (grid[x][y] != CORRUPTED) {
                grid[x][y] = 0;
            }
        }
    }
}

int trace_path(int grid[][GRID_SIZE], int sx, int sy, int ex, int ey) {
    int x, y, tx, ty, steps, tsteps;
    q_init();
    reset_grid(grid);

    q_push(sx, sy);
    grid[sx][sy] = 1;
    grid[ex][ey] = 0;

    while (q_size > 0) {
        q_pop(&x, &y);
        steps = grid[x][y];
        if (x == ex && y == ey) {
            break;
        }

        ty = y;
        // left
        if (x > 0) {
            tx = x - 1;
            tsteps = grid[tx][ty];
            if (tsteps == UN_VISITED) {
                grid[tx][ty] = steps + 1;
                q_push(tx, ty);
            }
        }

        // right
        if (x < GRID_SIZE - 1) {
            tx = x + 1;
            tsteps = grid[tx][ty];
            if (tsteps == UN_VISITED) {
                grid[tx][ty] = steps + 1;
                q_push(tx, ty);
            }
        }

        tx = x;
        // top
        if (y > 0) {
            ty = y - 1;
            tsteps = grid[tx][ty];
            if (tsteps == UN_VISITED) {
                grid[tx][ty] = steps + 1;
                q_push(tx, ty);
            }
        }

        // bottom
        if (y < GRID_SIZE - 1) {
            ty = y + 1;
            tsteps = grid[tx][ty];
            if (tsteps == UN_VISITED) {
                grid[tx][ty] = steps + 1;
                q_push(tx, ty);
            }
        }
    }

    return grid[ex][ey] - 1;
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

    int grid[GRID_SIZE][GRID_SIZE] = {0};
    int count = 0;
    char line[16];

    int x, y;
    while (count < MAX_BYTES) {
        fgets(line, sizeof(line), file);
        sscanf(line, "%d,%d", &x, &y);
        grid[x][y] = -1; // corrupted
        count++;
    }

    printf("pixel: %d,%d\n", x, y);
    int sx = 0;
    int sy = 0;
    int ex = 70;
    int ey = 70;
    int steps = trace_path(grid, sx, sy, ex, ey);
    printf("min steps: %d\n", steps);

    while (steps > 0 && fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%d", &x, &y);
        grid[x][y] = -1; // corrupted
        count++;
        steps = trace_path(grid, sx, sy, ex, ey);
        /* printf("pixel: %d,%d steps: %d\n", x, y, steps); */
    }

    /* for (int i = 0; i < GRID_SIZE; i++) { */
    /*     for (int j = 0; j < GRID_SIZE; j++) { */
    /*         printf(" %3d ", grid[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    printf("pixel: %d,%d\n", x, y);
    fclose(file);
    return 0;
}
