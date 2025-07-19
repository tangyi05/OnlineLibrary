#ifndef MAINFUNC_H
#define MAINFUNC_H
#include <stdio.h>
#include <stdlib.h>

typedef struct BOOK BOOK;

struct BOOK {
    char title[30];
    char author[30];
    char publisher[30];
    int borrowed;
}; 

int book_catalog(BOOK *lib, int total, int available, int borrowed);
void available_book_catalog(BOOK *lib, int total, int available);
void borrowed_book_catalog(BOOK *lib, int total, int borrowed);

int add_book(BOOK *lib, int *available);
int print_book(BOOK *lib, int total, int book_num);

int search_menu(BOOK *lib, int total);
int search_by_title(BOOK *lib, int total, char *p_title);
int search_by_publisher(BOOK *lib, int total, char *p_publisher);
int search_by_author(BOOK *lib, int total, char *p_author);

int rent_book(BOOK *lib, int total, int *available, int *borrowed);
int return_book(BOOK *lib, int total, int *available, int *borrowed);


#endif