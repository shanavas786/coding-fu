#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ROBOTS 1024
#define X_TILES 101
#define Y_TILES 103

/* #define X_TILES 11 */
/* #define Y_TILES 7 */

typedef struct robot {
    int px;
    int py;
    int vx;
    int vy;
} robot;

int find_cristmas_tree(robot *rbts, int num_robots) {
    int cols[X_TILES] = {0};
    int rows[Y_TILES] = {0};
    int grid[X_TILES][Y_TILES] = {0};

    for (int i = 0; i < num_robots; i++) {
        robot *rbt = &rbts[i];
        cols[rbt->px] = 1;
        rows[rbt->py] = 1;
        grid[rbt->px][rbt->py] = 1;
    }

    for (int i = 0; i < X_TILES; i++) {
        for (int j = 0; j < Y_TILES; j++) {
            if (grid[i][j] == 0) {
                printf(" ");
            } else {
                printf("%d", grid[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}

void move(robot *rbt, int iter) {
    int x = (rbt->px + (rbt->vx * iter)) % X_TILES;
    if (x < 0) {
        x = X_TILES + x;
    }
    rbt->px = x;

    int y = (rbt->py + (rbt->vy * iter)) % Y_TILES;
    if (y < 0) {
        y = Y_TILES + y;
    }
    rbt->py = y;
}

void move_all(robot *rbts, int num_robots, int iter) {
    for (int i = 0; i < num_robots; i++) {
        robot *rbt = &rbts[i];
        move(rbt, iter);
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

    robot robots[NUM_ROBOTS];
    robot robots1[NUM_ROBOTS];
    memset(&robots, 0, sizeof(robots));
    memset(&robots1, 0, sizeof(robots1));

    int num_robots = 0;
    char line[256] = {0};

    while (fgets(line, sizeof(line), file)) {
        int px, py, vx, vy;
        sscanf(line, "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
        robots[num_robots].px = px;
        robots[num_robots].py = py;
        robots[num_robots].vx = vx;
        robots[num_robots].vy = vy;

        robots1[num_robots].px = px;
        robots1[num_robots].py = py;
        robots1[num_robots].vx = vx;
        robots1[num_robots].vy = vy;
        num_robots++;
    }
    fclose(file);

    int iterations = 100;
    int qrts[4] = {0};
    int qrt;

    for (int i = 0; i < num_robots; i++) {
        robot *rbt = &robots[i];
        move(rbt, iterations);
        qrt = -1;

        int col = -1;
        if (rbt->px < X_TILES / 2) {
            col = 0;
        } else if (rbt->px > X_TILES / 2) {
            col = 1;
        }

        int row = -1;
        if (rbt->py < Y_TILES / 2) {
            row = 0;
        } else if (rbt->py > Y_TILES / 2) {
            row = 1;
        }

        if (col >= 0 && row >= 0) {
            qrt = col * 2 + row;
            qrts[qrt]++;
        }
    }

    long score = 1;
    for (int i = 0; i < 4; i++) {
        score *= qrts[i];
    }

    printf("safety factor: %ld\n", score);

    int moves = 0;
    int min_safety_score = 0;
    int moves_min_score = 0;

    for (int i = 0; i < (X_TILES * Y_TILES); i++) {
        moves++;
        memset(&qrts, 0, sizeof(qrts));

        for (int i = 0; i < num_robots; i++) {
            robot *rbt = &robots1[i];
            move(rbt, 1);
            qrt = -1;

            int col = -1;
            if (rbt->px < X_TILES / 2) {
                col = 0;
            } else if (rbt->px > X_TILES / 2) {
                col = 1;
            }

            int row = -1;
            if (rbt->py < Y_TILES / 2) {
                row = 0;
            } else if (rbt->py > Y_TILES / 2) {
                row = 1;
            }

            if (col >= 0 && row >= 0) {
                qrt = col * 2 + row;
                qrts[qrt]++;
            }
        }

        score = qrts[0] * qrts[1] * qrts[2] * qrts[3];

        if (min_safety_score == 0 || score < min_safety_score) {
            min_safety_score = score;
            moves_min_score = moves;
        }
    }

    printf("moves to form a tree: %d min_score: %d\n", moves_min_score, min_safety_score);
    return 0;
}
