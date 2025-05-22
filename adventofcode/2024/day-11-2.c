#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE 16384
long long CACHE[CACHE_SIZE][100];

long long power(int base, int size) {
  long long ret = 1;
  for (int i = 0; i < size; i++) {
    ret *= base;
  }

  return ret;
}

// returns the number of stones after n blinks
long long blink(long long num, int n) {
  if (num < CACHE_SIZE && CACHE[num][n] != -1) {
    return CACHE[num][n];
  }

  long long ret = 0;

  if (n == 0) {
    ret = 1;
  } else if (num == 0) {
    ret = blink(1, n - 1);
  } else {
    int digits = num_digits(num);
    if (digits % 2 != 0) {
      ret = blink(num * 2024, n - 1);
    } else {
      long long pwr = power(10, digits / 2);
      long long left = num / pwr;
      long long right = num % pwr;
      ret = blink(left, n - 1) + blink(right, n - 1);
    }
  }

  if (num < CACHE_SIZE) {
    CACHE[num][n] = ret;
  }

  return ret;
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

  for (int i = 0; i < CACHE_SIZE; i++) {
    for (int j = 0; j < 100; j++) {
      CACHE[i][j] = -1;
    }
  }

  long long arr[256];
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

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += blink(arr[i], 25);
  }
  printf("num of stones after 25 blinks: %lld\n", ans);

  ans = 0;
  for (int i = 0; i < n; i++) {
    ans += blink(arr[i], 75);
  }

  printf("num of stones after 75 blinks: %lld\n", ans);
  return 0;
}
