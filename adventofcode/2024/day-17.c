#include "libs/utils.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP_ADV 0
#define OP_BXL 1
#define OP_BST 2
#define OP_JNZ 3
#define OP_BXC 4
#define OP_OUT 5
#define OP_BDV 6
#define OP_CDV 7

int modulo(int a, int b) {
    int res = a % b;
    if (res < 0) {
        res += b;
    }

    return res;
}

int get_combo_op(int opr, long a, long b, long c) {
    int res = opr;
    switch (opr) {
    case 0:
    case 1:
    case 2:
    case 3:
        res = opr;
        break;
    case 4:
        res = a;
        break;
    case 5:
        res = b;
        break;
    case 6:
        res = c;
        break;
    case 7:
    default:
        break;
    }

    return res;
}

int exec(int program[], int len_program, int *inp, long *a, long *b, long *c) {
    int opcode;
    long opr;
    long num, denom;

    while (*inp < len_program) {

        opcode = program[(*inp)++];
        opr = program[(*inp)++];

        switch (opcode) {
        case OP_ADV:
            num = *a;
            opr = get_combo_op(opr, *a, *b, *c);
            denom = (long)pow(2, opr);
            *a = (long)(num / denom);
            break;
        case OP_BXL:
            *b = *b ^ opr;
            break;
        case OP_BST:
            opr = get_combo_op(opr, *a, *b, *c);
            *b = modulo(opr, 8);
            break;
        case OP_JNZ:
            if (*a != 0) {
                *inp = opr;
            }
            break;
        case OP_BXC:
            *b = *b ^ *c;
            break;

        case OP_OUT:
            opr = get_combo_op(opr, *a, *b, *c);
            return modulo(opr, 8);
            break;

        case OP_BDV:
            num = *a;
            opr = get_combo_op(opr, *a, *b, *c);
            denom = (long)pow(2, opr);
            *b = (long)(num / denom);
            break;

        case OP_CDV:
            num = *a;
            opr = get_combo_op(opr, *a, *b, *c);
            denom = (long)pow(2, opr);
            *c = (long)(num / denom);
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

    char line[1024];
    long a, b, c;
    int program[1024] = {0};
    int len_program = 0;

    fgets(line, sizeof(line), file);
    sscanf(line, "Register A: %ld", &a);

    fgets(line, sizeof(line), file);
    sscanf(line, "Register B: %ld", &b);

    fgets(line, sizeof(line), file);
    sscanf(line, "Register C: %ld", &c);

    fgets(line, sizeof(line), file); // empty line

    fgets(line, sizeof(line), file);

    for (int i = 0; i < strlen(line); i++) {
        if (line[i] >= '0' && line[i] < '8') {
            program[len_program++] = line[i] - '0';
        }
    }

    int inp = 0;
    int opcode;
    long opr;
    long num, denom;

    while (inp < len_program) {
        opcode = program[inp++];
        opr = program[inp++];

        switch (opcode) {
        case OP_ADV:
            num = a;
            opr = get_combo_op(opr, a, b, c);
            denom = (long)pow(2, opr);
            a = (long)(num / denom);
            break;
        case OP_BXL:
            b = b ^ opr;
            break;
        case OP_BST:
            opr = get_combo_op(opr, a, b, c);
            b = modulo(opr, 8);
            break;
        case OP_JNZ:
            if (a != 0) {
                inp = opr;
            }
            break;
        case OP_BXC:
            b = b ^ c;
            break;

        case OP_OUT:
            opr = get_combo_op(opr, a, b, c);
            printf("%d,", modulo(opr, 8));
            break;

        case OP_BDV:
            num = a;
            opr = get_combo_op(opr, a, b, c);
            denom = (long)pow(2, opr);
            b = (long)(num / denom);
            break;

        case OP_CDV:
            num = a;
            opr = get_combo_op(opr, a, b, c);
            denom = (long)pow(2, opr);
            c = (long)(num / denom);
            break;
        }
    }

    printf("\n");

    long q1[1024] = {0};
    long q2[1024] = {0};
    int step = 0;
    long *curr_q = q1;
    long *next_q = q2;
    int curr_q_size = 1;
    int next_q_size = 0;

    while (step < len_program) {
        /* printf("step: %d\n", step); */
        int candidate = program[len_program - step - 1];
        for (int i = 0; i < curr_q_size; i++) {
            long start = curr_q[i] * 8;
            for (long val = start; val < start + 8; val++) {
                a = val;
                inp = 0;
                int res = exec(program, len_program, &inp, &a, &b, &c);
                if (res == candidate) {
                    /* printf("found a: %ld\n", val); */
                    next_q[next_q_size++] = val;
                }
            }
        }

        long *temp = curr_q;
        int tmp = curr_q_size;

        curr_q = next_q;
        curr_q_size = next_q_size;
        next_q = curr_q;
        next_q_size = 0;
        step++;
    }

    long min_a = min(curr_q, curr_q_size);
    printf("min a: %ld\n", min_a);

    fclose(file);
    return 0;
}
