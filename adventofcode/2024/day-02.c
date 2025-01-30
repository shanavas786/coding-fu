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

int is_safe(int arr[], int size) {
  int prev_order = 0;
  int current_order;
  int prev_number, current_number;
  int safe = 1;

  for (int i = 1; i < size; i++) {
    prev_number = arr[i - 1];
    current_number = arr[i];
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

  return safe;
}

int is_safe_with_dampener(int arr[], int size) {
  int *arr_copy = (int *) malloc((size - 1) * sizeof(int));
  int safe = 0;

  for (int i = 0; i < size; i++) {
    int idx = 0;
    while (idx < size) {
      if (idx < i) {
        arr_copy[idx] = arr[idx];
      } else if (idx > i) {
        arr_copy[idx - 1] = arr[idx];
      }
      idx++;
    }

    if (is_safe(arr_copy, size - 1)) {
      safe = 1;
      break;
    }
  }

  free(arr_copy);
  return safe;
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
  int safe_reports_with_dampner = 0;
  char *endptr = line;

  int arr[10] = {0};
  int n = 0;
  int number;

  while (fgets(line, sizeof(line), file)) {
    n = 0;
    endptr = line;
    number = strtol(endptr, &endptr, 10);
    arr[n++] = number;
    while (*endptr != EOF && *endptr != '\n') {
      number = strtol(endptr, &endptr, 10);
      arr[n++] = number;
    }
    if (is_safe(arr, n)) {
      safe_reports++;
      safe_reports_with_dampner++;
    } else if (is_safe_with_dampener(arr, n)) {
      safe_reports_with_dampner++;
    }
  }

  fclose(file);

  printf("number of safe reports: %d\n", safe_reports);
  printf("number of safe reports with dampner: %d\n", safe_reports_with_dampner);

  return 0;
}
