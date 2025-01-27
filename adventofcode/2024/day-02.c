#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int compare(int left, int right) {
  // -1 left > right
  // 0 left == right
  // 1 left < right
  if (left > right) {
    return -1;
  } else if (left < right) {
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
  int safe_reports = 0;
  int current_number = 0;
  int prev_number = 0;
  char *endptr = line;
  int prev_order = 0;
  int current_order = 0;
  int safe;

  while (fgets(line, sizeof(line), file)) {
    safe = 1;
    endptr = line;
    prev_order = 0;
    current_number = strtol(endptr, &endptr, 10);
    while (*endptr != EOF && *endptr != '\n') {
      prev_number = current_number;
      current_number = strtol(endptr, &endptr, 10);
      current_order = compare(prev_number, current_number);

      if(abs(prev_number - current_number) <= 3 && abs(prev_number - current_number) > 0) {
        if (prev_order == 0 || current_order == prev_order) {
          prev_order = current_order;
          continue;
        }
      }

      safe = 0;
      break;
    }
    if (safe) {
      safe_reports++;
    }
  }

  printf("number of safe reports: %d\n", safe_reports);

  return 0;
}
