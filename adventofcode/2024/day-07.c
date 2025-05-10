#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_valid(long long result, int operands[], int size) {
    if (size == 1) {
        return result == operands[0];
    }

    long long max_res = 1;
    int min_res = 0;
    for (int i = 0; i < size; i++) {
        if (operands[i] != 1) {
            max_res *= operands[i];
        } else {
            max_res += operands[i];
        }

        if (operands[i] != 1) {
            min_res += operands[i];
        }
    }

    if (result > max_res || result < min_res) {
        return 0; // not attainable
    }
    if (result == max_res || result == min_res) {
        return 1;
    }
    return is_valid(result - operands[size - 1], operands, size - 1) ||
        (result % operands[size - 1] == 0 && is_valid(result / operands[size - 1], operands, size - 1));
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


  char line[256];
  long long calib_sum = 0;
  char *endptr;
  long long res;
  int operands[256];
  int size;

  while (fgets(line, sizeof(line), file)) {
    size = 0;
    res = strtol(line, &endptr, 10);
    endptr++; // skip ':' character
    while (*endptr != EOF && *endptr != '\n') {
        operands[size++] = strtol(endptr, &endptr, 10);
    }

    if (is_valid(res, operands, size)) {
        printf("valid: %s", line);
        calib_sum += res;
    } else {
        printf("invalid: %s", line);
    }
  }

  printf("sum of calibrated eqn results: %lld\n", calib_sum);
  return 0;
}
