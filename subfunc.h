#ifndef SUBFUNC_H
#define SUBFUNC_H
#include <stdio.h>

void transition();
int copy(char *dest, char *copy);
int compare(char *arr1, char *arr2);
void change_buffer(char *input);
int valid_book_num(int book_num, int total);
int not_y_or_n(char answer);

#endif