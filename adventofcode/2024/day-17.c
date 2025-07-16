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

int get_combo_op(int opr, int a, int b, int c) {
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
    int a, b, c;
    int program[1024] = {0};
    int len_program = 0;

    fgets(line, sizeof(line), file);
    sscanf(line, "Register A: %d", &a);

    fgets(line, sizeof(line), file);
    sscanf(line, "Register B: %d", &b);

    fgets(line, sizeof(line), file);
    sscanf(line, "Register C: %d", &c);

    fgets(line, sizeof(line), file); // empty line

    fgets(line, sizeof(line), file);

    for (int i = 0; i < strlen(line); i++) {
        if (line[i] >= '0' && line[i] < '8') {
            program[len_program++] = line[i] - '0';
        }
    }

    int inp = 0;
    int opcode;
    int opr;
    int num, denom;

    while (inp < len_program) {
        opcode = program[inp++];
        opr = program[inp++];

        switch (opcode) {
        case OP_ADV:
            num = a;
            opr = get_combo_op(opr, a, b, c);
            denom = (int)pow(2, opr);
            a = (int)(num / denom);
            break;
        case OP_BXL:
            b = b ^ opr;
            break;
        case OP_BST:
            opr = get_combo_op(opr, a, b, c);
            b = modulo(opr, 8);
            if (b < 0) {
                b = 8 - b;
            }
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
            denom = (int)pow(2, opr);
            b = (int)(num / denom);
            break;

        case OP_CDV:
            num = a;
            opr = get_combo_op(opr, a, b, c);
            denom = (int)pow(2, opr);
            c = (int)(num / denom);
            break;
        }
    }

    fclose(file);
    return 0;
}
