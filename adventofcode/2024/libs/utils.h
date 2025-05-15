#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>

int fread_all(FILE *file, char **buffer);

int scan_int(char **p);


void swap(int *i, int *j);
void q_sort(int *array, int size);

char *ptrmin(char * ptr1, char * ptr2);

char **transpose(char **grid, int rows, int cols);

int find(int arr[], int size, int elem);

char **read_maze(FILE *file,int *rows,int *cols);

#endif // UTILS_H_
