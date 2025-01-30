#include "utils.h"

int fread_all(FILE *file, char **buffer) {
  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  fseek(file, 0, SEEK_SET); /* same as rewind(f); */

  *buffer = malloc(fsize + 1);
  fread(*buffer, fsize, 1, file);

  return fsize;
}

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}


void q_sort(int *array, int size) {
  if (size < 2) {
    return;
  }

  int pivot = 0;
  int left = 0;
  int right = size - 1;

  while (left < right) {
    while(array[left] <= array[pivot] && left < size) {
      left++;
    }

    while(array[right] > array[pivot] && right > 0) {
      right--;
    }

    if (left < right) {
      swap(array + left, array + right);
    }
  }

  swap(array + pivot, array + right);

  q_sort(array, right );
  q_sort(array + right + 1, size - right - 1);
}
