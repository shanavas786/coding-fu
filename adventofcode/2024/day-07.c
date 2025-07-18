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
         (result % operands[size - 1] == 0 &&
          is_valid(result / operands[size - 1], operands, size - 1));
}

int is_valid_with_concat(long long result, int operands[], int size) {
  if (size == 1) {
    return result == operands[0];
  }

  int num = operands[size - 1];
  if (is_valid_with_concat(result - num, operands, size - 1)) {
    return 1;
  }

  if (result % num == 0 && is_valid_with_concat(result / num, operands, size - 1)) {
    return 1;
  }

  int order = 10;
  while (num % order != num) {
    order *= 10;
  }

  if ((num == result % order) && is_valid_with_concat(result / order, operands, size - 1)) {
    return 1;
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

  char line[256];
  long long calib_sum = 0;
  long long calib_sum2 = 0;
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
      /* printf("valid: %s", line); */
      calib_sum += res;
      calib_sum2 += res;
    } else if (is_valid_with_concat(res, operands, size)) {
      calib_sum2 += res;
    } else {
      /* printf("invalid: %s", line); */
    }
  }

  fclose(file);
  printf("sum of calibrated eqn results: %lld\n", calib_sum);
  printf("sum of calibrated eqn results2: %lld\n", calib_sum2);
  return 0;
}
