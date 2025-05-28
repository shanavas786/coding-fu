#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 1) {
    exit(1);
  }

  char *file_path = argv[1];
  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    exit(1);
  }

  int num1, num2;
  long sum = 0;
  long sum_enabled = 0;

  char *buffer = NULL;
  int size = fread_all(file, &buffer);
  char *p = buffer;
  char *doptr = NULL, *dontptr = NULL, *mulptr = NULL;
  int enabled = 1;

  for (;;) {
    mulptr = strstr(p, "mul(");
    doptr = strstr(p, "do()");
    dontptr = strstr(p, "don't()");

    if (mulptr == NULL) {
      break;
    }

    char *condptr = ptrmin(doptr, dontptr);
    if (ptrmin(mulptr, condptr) == condptr) {
      enabled = condptr == doptr;
      p = ++condptr;
      continue;
    }

    p = mulptr;
    // skip "mul("
    p += 4;
    num1 = scan_int(&p);
    if (*p != ',') {
      continue;
    }

    p++;
    num2 = scan_int(&p);

    if (*p == ')') {
      sum += num1 * num2;
      if (enabled) {
        sum_enabled += num1 * num2;
      }
    }
    p++;
  }

  free(buffer);
  fclose(file);

  printf("sum of multiplications: %ld\n", sum);
  printf("sum of enabled multiplications: %ld\n", sum_enabled);
  return 0;
}
