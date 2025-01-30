#include <stdlib.h>
#include <stdio.h>
#include "libs/utils.h"

int main(int argc, char *argv[]) {
  if (argc < 1) {
    exit(1);
  }

  char *file_path = argv[1];
  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    exit(1);
  }


  int *list1 = (int *) calloc(1000, sizeof(int));
  int *list2 = (int *) calloc(1000, sizeof(int));

  char line[256];
  int i = 0, j = 0;
  int count = 0;
  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%d   %d", &i, &j);
    list1[count] = i;
    list2[count] = j;
    count++;
  }

  fclose(file);

  q_sort(list1, count);
  q_sort(list2, count);

  /* for (int i = 0; i < count; i++) { */
  /*   printf("%d %d\n", list1[i],  list2[i]); */
  /* } */

  int dist_sum = 0;
  for (int i = 0; i < count; i++) {
    dist_sum += abs(list1[i] - list2[i]);
  }
  printf("total distance: %d\n", dist_sum);

  // part 2
  i = 0;
  j = 0;
  int similarity_score = 0;

  while (i < count - 1 || j < count - 1) {
    while (list1[i] != list2[j]) {
      if (list1[i] < list2[j] && i < count - 1) {
        i++;
      }

      if (list1[i] > list2[j] && j < count - 1) {
        j++;
      }

      if (i == count - 1 && j == count - 1) {
        break;
      }
    }

    if (list1[i] != list2[j]) {
      continue;
    }

    // now list1[i] and list2[j] are matching
    int left_count = 1;
    int right_count = 1;
    int number = list1[i];

    while (list1[i] == list1[i + 1]) {
      left_count++;
      i++;
    }
    i++;

    while (list2[j] == list2[j + 1]) {
      right_count++;
      j++;
    }
    j++;

    similarity_score += number * left_count * right_count;
  }

  free(list1);
  free(list2);

  printf("similarity score: %d\n", similarity_score);

  return 0;
}
