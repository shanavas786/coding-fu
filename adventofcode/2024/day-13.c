#include "libs/utils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long solve_puzzle_2(int ax, int ay, int bx, int by, long long px, long long py) {
    long long token = 0;

    // | ax  bx | | a | => | px |
    // | ay  by | | b |    | py |

    long long det = (ax * by) - (ay * bx);
    long long deta = (px * by) - (py * bx);
    long long detb = (ax * py) - (ay * px);

    /* printf("det: %lld deta: %lld detb: %lld\n", det, deta, detb); */
    if (det != 0) {
        long long a = deta / det;
        long long b = detb / det;
        if ((a * ax + b * bx == px) && (a * ay + b * by == py)) {
            if (a >= 0 && b >= 0) {
                token = 3 * a + b;
            }
        }
    }
    return token;
}

int solve_puzzle(int ax, int ay, int bx, int by, int px, int py) {
    int token = 0;

    // | ax  bx | | a | => | px |
    // | ay  by | | b |    | py |

    int det = (ax * by) - (ay * bx);
    int deta = (px * by) - (py * bx);
    int detb = (ax * py) - (ay * px);

    if (det != 0) {
        int a = deta / det;
        int b = detb / det;
        if ((a * ax + b * bx == px) && (a * ay + b * by == py)) {
            if (a >= 0 && a <= 100 && b >= 0 && b <= 100) {
                token = 3 * a + b;
            }
        }
    }
    return token;
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

    long tokens = 0;
    long long tokens2 = 0;
    char line[256];
    int ax, ay, bx, by, px, py;

    do {
        fgets(line, sizeof(line), file); // empty line
        sscanf(line, "Button A: X+%d, Y+%d", &ax, &ay);
        fgets(line, sizeof(line), file);
        sscanf(line, "Button B: X+%d, Y+%d", &bx, &by);
        fgets(line, sizeof(line), file);
        sscanf(line, "Prize: X=%d, Y=%d", &px, &py);
        tokens += solve_puzzle(ax, ay, bx, by, px, py);
        tokens2 += solve_puzzle_2(ax, ay, bx, by, px + 10000000000000ll, py + 10000000000000ll);
    } while (fgets(line, sizeof(line), file));

    printf("total tokens: %ld\n", tokens);
    printf("total tokens2: %llu\n", tokens2);
}
