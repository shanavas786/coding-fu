#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/utils.h"

#define BUFF_SIZE 1024 * 1024 * 1024


int scan_int(char **p) {
    int num = 0;
    if ( **p < '0' || **p > '9') {
        return 0;
    }

    while (**p >= '0' && **p <= '9') {
        num = num * 10 + (**p - '0');
        (*p)++;
    }

    return num;
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

  int num1, num2;
  long sum = 0;

  char *buffer;
  int size = fread_all(file, &buffer);
  char *p = buffer;

  while((p = strstr(p, "mul("))) {
      // skip "mul("
      p += 4;
      num1 = scan_int(&p);
      if (*p != ',') {
          continue;
      }

      p++;
      num2 = scan_int( &p);

      if (*p == ')') {
          sum += num1 * num2;
      }
      p++;
  }


  printf("sum of multiplications: %ld\n", sum);
  return 0;
}
