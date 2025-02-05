#include "utils.h"
#include <stdlib.h>

/**
 * Read the entire file into a buffer
 */
int fread_all(FILE *file, char **buffer) {
  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  fseek(file, 0, SEEK_SET); /* same as rewind(f); */

  *buffer = malloc(fsize + 1);
  fread(*buffer, fsize, 1, file);

  return fsize;
}

/**
 * Parse given string as int
 * Returns a pointer to the first invalid character
 */
int scan_int(char **p) {
  int num = 0;
  if (**p < '0' || **p > '9') {
    return 0;
  }

  while (**p >= '0' && **p <= '9') {
    num = num * 10 + (**p - '0');
    (*p)++;
  }

  return num;
}

/**
 * swap to numbers
 */
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
    while (array[left] <= array[pivot] && left < size) {
      left++;
    }

    while (array[right] > array[pivot] && right > 0) {
      right--;
    }

    if (left < right) {
      swap(array + left, array + right);
    }
  }

  swap(array + pivot, array + right);

  q_sort(array, right);
  q_sort(array + right + 1, size - right - 1);
}

char *ptrmin(char *ptr1, char *ptr2) {
  if (ptr1 == NULL)
    return ptr2;

  if (ptr2 == NULL)
    return ptr1;

  if (ptr1 < ptr2)
    return ptr1;

  return ptr2;
}


// transpose a grid
// returns a new pointer to the transposed grid
char **transpose(char **grid, int rows, int cols) {

  // intialize tgrid
  char **tgrid = malloc(cols * sizeof(char *));
  for (int i = 0; i < cols; i++) {
    tgrid[i] = malloc((rows + 1)* sizeof(char));
  }


  for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
      tgrid[j][i] = grid[i][j];
    }
    tgrid[j][rows] = '\0';
  }

  return tgrid;
}



int find(int arr[], int size, int elem) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == elem)
      return 1;
  }

  return 0;
}
