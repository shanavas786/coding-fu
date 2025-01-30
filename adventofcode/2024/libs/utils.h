#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>

int fread_all(FILE *file, char **buffer);

int scan_int(char **p);


void swap(int *i, int *j);
void q_sort(int *array, int size);


#endif // UTILS_H_
