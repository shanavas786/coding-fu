#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE (256 * 256)

int fread_all(FILE *file, char **buffer);

int scan_int(char **p);

void swap(int *i, int *j);
void q_sort(int *array, int size);

char *ptrmin(char *ptr1, char *ptr2);

char **transpose(char **grid, int rows, int cols);

int find(int arr[], int size, int elem);

char **read_maze(FILE *file, int *rows, int *cols);

int num_digits(long long num);

// stack methods
void stack_init();

int stack_pop();

void stack_push(int val);

int stack_size();

long min(long arr[], int size);

#endif // UTILS_H_
