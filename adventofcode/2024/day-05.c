#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int **rules;

int compare(const int x, const int y) {
  // check if x has any rules
  if (rules[x - 1][0] != 0) {
    if (find(rules[x - 1] + 1, rules[x - 1][0], y)) {
      // x should come before y
      return -1;
    }
  }

  if (rules[y - 1][0] != 0) {
    if (find(rules[y - 1] + 1, rules[y - 1][0], x)) {
      // x should come after y
      return 1;
    }
  }

  // no particular order
  return 0;
}

int compare_gen(const void *x, const void *y) {
  return compare(*(int *)x, *(int *)y);
}

int check_validity(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < i; j++) {
      if (compare(arr[j], arr[i]) > 0) {
        // rule violated
        return 0;
      }
    }
  }

  return 1;
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

  char *str;
  int rows = 100;
  int cols = 100;

  char line[256];

  rules = (int **) malloc(rows * sizeof(int *));
  for (int i = 0; i < cols; i++) {
    rules[i] = (int *) malloc(cols * sizeof(int));
    rules[i][0] = 0; // number of rules for that page
  }

  int i = 0;
  int num1, num2;
  int *rule;
  while (fgets(line, sizeof(line), file)) {
    if (strncmp("\n", line, 1) == 0) {
      break;
    }
    sscanf(line, "%d|%d", &num1, &num2);
    rule = rules[num1 - 1];
    int num_rules = rule[0];
    rule[num_rules + 1] = num2;
    rule[0] += 1;
  }

  for (int i = 0; i < rows; i++) {
    rule = rules[i];
    /* print_rule(rule, i); */
  }

  int update[100];
  int pages = 0;
  int sum_ordered = 0;
  int sum_unordered = 0;
  while (fgets(line, sizeof(line), file)) {
    pages = 0;
    char *str = line;
    do {
      update[pages++] = strtol(str, &str, 10);
    } while((*str++) == ',');

    if (check_validity(update, pages)) {
      sum_ordered += update[pages / 2];
    } else {
      qsort(update, pages, sizeof(int), compare_gen);
      sum_unordered += update[pages / 2];
    }
  }

  for (int i = 0; i < rows; i++) {
    free(rules[i]);
  }
  free(rules);
  fclose(file);

  printf("sum of middle pages ordered: %d\n", sum_ordered);
  printf("sum of middle pages unordered: %d\n", sum_unordered);
  return 0;
}
