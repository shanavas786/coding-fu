#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


long power(int base, int size) {
  long ret = 1;
  for (int i = 0; i < size; i++) {
    ret *= base;
  }

  return ret;
}

long long *blink(long long *arr, int size, int *newsize) {
  long long *arr1 = calloc(size * 2, sizeof(long long));
  int idx = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] == 0) {
      arr1[idx++] = 1;
    } else {
      int digits = num_digits(arr[i]);
      if (digits % 2 == 0) {
        long pwr = power(10, digits / 2);
        long left = arr[i] / pwr;
        long right = arr[i] % pwr;
        arr1[idx++] = left;
        arr1[idx++] = right;
      } else {
        arr1[idx++] = arr[i] * 2024;
      }
    }
  }
  *newsize = idx;
  free(arr);
  return arr1;
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

  long long *arr = calloc(256, sizeof(long long));

  char line[256];
  char *endptr = line;

  fgets(line, sizeof(line), file);
  fclose(file);
  int n = 0;
  endptr = line;
  long long number;

  while (*endptr != EOF && *endptr != '\n') {
    number = strtol(endptr, &endptr, 10);
    arr[n++] = number;
  }

  int ans1 = 0;
  for (int i = 0; i < 25; i++) {
    arr = blink(arr, n, &n);
    if (i == 24) {
      ans1 = n;
    }
  }

  printf("num of stones after 25 blinks: %d\n", ans1);
  free(arr);
  return 0;
}
