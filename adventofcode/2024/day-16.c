#include "libs/utils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH 3
#define UNSET 0
#define VISITED 4

int ex, ey, sx, sy;
int CACHE[140][140][5] = {0};

int count_tiles(char **maze, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            count += CACHE[i][j][VISITED];
        }
    }

    return count;
}

void mark_tiles(char **maze, int rows, int cols, int x, int y, int dir) {
    // find number of tiles to reach 'S' from x,y tile
    int tiles = 0;
    int score = CACHE[y][x][dir];

    CACHE[y][x][VISITED] = 1;

    if (x == sx && y == sy) {
        return;
    }

    // check if any other direction is a valid path
    for (int i = 0; i < 4; i++) {
        if (score - CACHE[y][x][i] == 1000) {
            mark_tiles(maze, rows, cols, x, y, i);
        }
    }

    switch (dir) {
    case EAST:
        if (x - 1 > 0 && CACHE[y][x - 1][dir] == score - 1) {
            mark_tiles(maze, rows, cols, x - 1, y, dir);
        }
        break;
    case SOUTH:
        if (y - 1 > 0 && CACHE[y - 1][x][dir] == score - 1) {
            mark_tiles(maze, rows, cols, x, y - 1, dir);
        }
        break;
    case WEST:
        if (x + 1 < cols && CACHE[y][x + 1][dir] == score - 1) {
            mark_tiles(maze, rows, cols, x + 1, y, dir);
        }
        break;
    case NORTH:
        if (y + 1 < rows && CACHE[y + 1][x][dir] == score - 1) {
            mark_tiles(maze, rows, cols, x, y + 1, dir);
        }
        break;
    default:
        break;
    }
}

int get_min_score() {
    int score = 0;
    for (int i = 0; i < 4; i++) {
        if (score == 0) {
            score = CACHE[ey][ex][i];
            continue;
        }

        if (CACHE[ey][ex][i] != 0 && CACHE[ey][ex][i] < score) {
            score = CACHE[ey][ex][i];
        }
    }

    return score;
}

int get_min_score_dir(int score) {
    for (int i = 0; i < 4; i++) {
        if (score == CACHE[ey][ex][i])
            return i;
    }
    return 0;
}

void find_score(char **maze, int rows, int cols, int x, int y, int dir,
                int iter) {
    /* printf("x: %2d, y: %2d, dir: %2d, iter: %d\n", x, y, dir, iter); */

    int score, cache;
    char sym;
    int dx, dy;
    int min_score = get_min_score();

    // east
    if (dir % 2 == 0) {
        dx = x - dir + 1;
        if (dx < cols && dx > 0) {
            score = CACHE[y][x][dir] + 1;
            cache = CACHE[y][dx][dir];
            sym = maze[y][dx];
            if (sym == '#') {
                CACHE[y][dx][EAST] = -1;
                CACHE[y][dx][NORTH] = -1;
                CACHE[y][dx][WEST] = -1;
                CACHE[y][dx][SOUTH] = -1;
            } else if (cache == UNSET || score < cache) {
                CACHE[y][dx][dir] = score;
                /* printf("setting x: %2d, y: %2d, dir: %d to score: %4d\n", dx,
                 * y, */
                /*        dir, score); */
                min_score = get_min_score();
                if (min_score == 0 || score < min_score) {
                    find_score(maze, rows, cols, dx, y, dir, iter + 1);
                }
            }
        }

        // north
        if (y > 0) {
            score = CACHE[y][x][dir] + 1001;
            if (CACHE[y][x][NORTH] == 0 || CACHE[y][x][NORTH] > score - 1) {
                CACHE[y][x][NORTH] = score - 1;
            }

            cache = CACHE[y - 1][x][NORTH];
            sym = maze[y - 1][x];

            if (sym == '#') {
                CACHE[y - 1][x][EAST] = -1;
                CACHE[y - 1][x][NORTH] = -1;
                CACHE[y - 1][x][WEST] = -1;
                CACHE[y - 1][x][SOUTH] = -1;
            } else if (cache == UNSET || score < cache) {
                CACHE[y - 1][x][NORTH] = score;
                /* printf("setting x: %2d, y: %2d, dir: %d to score: %4d\n", x,
                 */
                /*        y - 1, NORTH, score); */
                min_score = get_min_score();
                if (min_score == 0 || score < min_score) {
                    find_score(maze, rows, cols, x, y - 1, NORTH, iter + 1);
                }
            }
        }

        // south
        if (y + 1 < rows) {
            score = CACHE[y][x][dir] + 1001;
            if (CACHE[y][x][SOUTH] == 0 || CACHE[y][x][SOUTH] > score - 1) {
                CACHE[y][x][SOUTH] = score - 1;
            }

            cache = CACHE[y + 1][x][SOUTH];
            sym = maze[y + 1][x];

            if (sym == '#') {
                CACHE[y + 1][x][EAST] = -1;
                CACHE[y + 1][x][NORTH] = -1;
                CACHE[y + 1][x][WEST] = -1;
                CACHE[y + 1][x][SOUTH] = -1;
            } else if (cache == UNSET || score < cache) {
                CACHE[y + 1][x][SOUTH] = score;
                /* printf("setting x: %2d, y: %2d, dir: %d to score: %4d\n", x,
                 */
                /*        y + 1, SOUTH, score); */
                min_score = get_min_score();
                if (min_score == 0 || score < min_score) {
                    find_score(maze, rows, cols, x, y + 1, SOUTH, iter + 1);
                }
            }
        }
    } else {
        dy = y - dir + 2;
        if (dy < rows && dy > 0) {
            score = CACHE[y][x][dir] + 1;
            cache = CACHE[dy][x][dir];
            sym = maze[dy][x];
            if (sym == '#') {
                CACHE[dy][x][EAST] = -1;
                CACHE[dy][x][NORTH] = -1;
                CACHE[dy][x][WEST] = -1;
                CACHE[dy][x][SOUTH] = -1;
            } else if (cache == UNSET || score < cache) {
                CACHE[dy][x][dir] = score;
                /* printf("setting x: %2d, y: %2d, dir: %d to score: %4d\n", x,
                 * dy, */
                /*        dir, score); */
                min_score = get_min_score();
                if (min_score == 0 || score < min_score) {
                    find_score(maze, rows, cols, x, dy, dir, iter + 1);
                }
            }
        }

        // west
        if (x > 0) {
            score = CACHE[y][x][dir] + 1001;
            if (CACHE[y][x][WEST] == 0 || CACHE[y][x][WEST] > score - 1) {
                CACHE[y][x][WEST] = score - 1;
            }

            cache = CACHE[y][x - 1][WEST];
            sym = maze[y][x - 1];

            if (sym == '#') {
                CACHE[y][x - 1][EAST] = -1;
                CACHE[y][x - 1][NORTH] = -1;
                CACHE[y][x - 1][WEST] = -1;
                CACHE[y][x - 1][SOUTH] = -1;
            } else if (cache == UNSET || score < cache) {
                CACHE[y][x - 1][WEST] = score;
                /* printf("setting x: %2d, y: %2d, dir: %d to score: %4d\n", x -
                 * 1, */
                /*        y, WEST, score); */
                min_score = get_min_score();
                if (min_score == 0 || score < min_score) {
                    find_score(maze, rows, cols, x - 1, y, WEST, iter + 1);
                }
            }
        }

        // east
        if (x + 1 < cols) {
            score = CACHE[y][x][dir] + 1001;
            if (CACHE[y][x][EAST] == 0 || CACHE[y][x][EAST] > score - 1) {
                CACHE[y][x][EAST] = score - 1;
            }

            cache = CACHE[y][x + 1][EAST];
            sym = maze[y][x + 1];

            if (sym == '#') {
                CACHE[y][x + 1][EAST] = -1;
                CACHE[y][x + 1][NORTH] = -1;
                CACHE[y][x + 1][WEST] = -1;
                CACHE[y][x + 1][SOUTH] = -1;
            } else if (cache == UNSET || score < cache) {
                CACHE[y][x + 1][EAST] = score;
                /* printf("setting x: %2d, y: %2d, dir: %d to score: %4d\n", x +
                 * 1, */
                /*        y, EAST, score); */
                min_score = get_min_score();
                if (min_score == 0 || score < min_score) {
                    find_score(maze, rows, cols, x + 1, y, EAST, iter + 1);
                }
            }
        }
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

    char **maze;
    int rows, cols;

    maze = read_maze(file, &rows, &cols);

    sx = 1;
    sy = rows - 2;
    ex = cols - 2;
    ey = 1;

    printf("rows: %d, cols: %d\n", rows, cols);
    printf("sx: %d, sy: %d\n", sx, sy);
    printf("ex: %d, ey: %d\n", ex, ey);
    CACHE[sy][sx][EAST] = 1;
    CACHE[sy][sx][NORTH] = 1001;
    CACHE[sy][sx][SOUTH] = 1001;

    find_score(maze, rows, cols, sx, sy, EAST, 1);

    /* printf("cache(ex, ey) east : %d\n", CACHE[ey][ex][EAST]); */
    /* printf("cache(ex, ey) south : %d\n", CACHE[ey][ex][SOUTH]); */
    /* printf("cache(ex, ey) west : %d\n", CACHE[ey][ex][WEST]); */
    /* printf("cache(ex, ey) north : %d\n", CACHE[ey][ex][NORTH]); */

    /* printf("------------------\n"); */
    /* for (int i = 0; i < rows; i++) { */
    /*     for (int j = 0; j < cols; j++) { */
    /*         printf("r: %2d, c:%2d, e: %5d, s: %5d, w:%5d, n: %5d\n", i, j, */
    /*                CACHE[i][j][EAST], CACHE[i][j][SOUTH], CACHE[i][j][WEST],
     */
    /*                CACHE[i][j][NORTH]); */
    /*     } */
    /*     printf("----\n"); */
    /* } */
    /* printf("------------------\n"); */

    int min_score = get_min_score();
    int min_score_dir = get_min_score_dir(min_score);
    printf("min score: %d\n", min_score - 1);

    mark_tiles(maze, rows, cols, ex, ey, min_score_dir);
    printf("num tiles: %d\n", count_tiles(maze, rows, cols));

    /* for (int i = 0; i < rows; i++) { */
    /*     for (int j = 0; j < cols; j++) { */
    /*         printf("%d ", CACHE[i][j][VISITED]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    for (int i = 0; i < rows; i++) {
        free(maze[i]);
    }
    free(maze);
    fclose(file);
}
