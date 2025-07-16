#include <stdio.h>
#include "mainfunc.h"
#include "subfunc.h"



int book_catalog(char lib[][3][50], int total, char rent_lib[][3][50], int rent_total) {
    int option = 1; //User Input to navigate search menu

    while (option != 0) {
        
        //User Interface
        printf("\n----------- BOOK CATALOG -----------\n\n");
        printf("Back : 0\n");
        printf("Available Books : 1\n");
        printf("Rented Books: 2 \n");
        
        printf(": ");
        scanf("%d", &option); //Get user's input
        getchar();  //Getting rid of \0 from the stdin => preventing unintentional input

        switch(option) {
            case 0: 
                return 0; //Return to lobby (still can stay on lobby b/c command from lobby is still 2)
                
            case 1: 
                available_book_catalog(lib, total);
                transition();
                break;

            case 2: 
                rented_book_catalog(rent_lib, rent_total);
                transition();
                break;
            default: 
                printf("Error: Wrong Command\n"); 
                break;
            }
        }

    return 0;
}

int available_book_catalog(char lib[][3][50], int total) {
    int i = 1;
    
    printf("\n*********** AVAILABLE BOOKS ***********\n");

    if (total == 0) {
        printf("\nWe are currently out of book:(\n");
        return 0;
    }

    for (; i <= total; i++) {
        print_book(lib, total, i);
    }
    
    return 0;
}

int rented_book_catalog(char rent_lib[][3][50], int rent_total) {
    int i = 1;
    
    printf("\n*********** RENTED BOOKS ***********\n");

    if (rent_total == 0) {
        printf("\nThere isn't any book rented!\n");
        return 0;
    }

    for (; i <= rent_total; i++) {
        print_book(rent_lib, rent_total, i);
    }
    
    return 0;
}

int search_menu(char lib[][3][50], int total) {   //Search shouldn't change the value of total, so it shouldn't be a pointer
    int option = 1; //User Input to navigate search menu

    while (option != 0) {
        
        //User Interface
        printf("\n----------- SEARCH -----------\n\n");
        printf("Back : 0\n");
        printf("Search by Book Number: 1 \n");
        printf("Search by Title: 2 \n");
        printf("Search by Author: 3 \n");
        printf("Search by Publisher : 4 \n");
        
        printf(": ");
        scanf("%d", &option); //Get user's input
        getchar();  //Getting rid of \0 from the stdin => preventing unintentional input

        switch(option) {
            case 0: 
                return 0; //Return to lobby (still can stay on lobby b/c command from lobby is still 2)
                
            case 1:

                {
                    int book_num; //Create holder for user input

                    printf("\n");
                    printf("Book Number: ");
                    scanf("%d", &book_num);
                    print_book(lib, total, book_num);
                    getchar();
                    transition();

                    break;
                }
                
            case 2:

                {
                    char title[50]; 

                    printf("\n");
                    printf("Title : ");
                    fgets(title, 50, stdin);
                    change_buffer(title); //modifying buffer to avoid doing \n

                    search_by_title(lib, total, title);
                    break;
                }

            case 3:
                {
                    char author[50];

                    printf("\n");
                    printf("Author : ");
                    fgets(author, 50, stdin);
                    change_buffer(author);

                    search_by_author(lib, total, author);
                    break;
                }

            case 4:

                {
                    char publisher[50];

                    printf("\n");
                    printf("Publisher : ");
                    fgets(publisher, 50, stdin);
                    change_buffer(publisher);
                    
                    search_by_publisher(lib, total, publisher);
                    break;
                }

            default:
                printf("Error: Wrong Command\n"); //Handling error
                break;
            

        }

    }

    return 0;
    
}


int search_by_title(char lib[][3][50], int total, char *p_title) {
    int i;
    int is_exist = 0;

    for (i = 0; i < total; i++) {
        if (compare(lib[i][0], p_title)) {

            is_exist = 1;
            print_book(lib, total, i+1);

        } 
    } 

    //Handling Error
    if (is_exist == 0) {
        printf("\nSorry, \"%s\" doesn't exist in our databse.\n", p_title);
    }

    transition();

    return 0;

}

int search_by_author(char lib[][3][50], int total, char *p_author) {
    int i;
    int is_exist = 0; //Handling Error

    for (i = 0; i < total; i++) {
        if (compare(lib[i][1], p_author)) {

            is_exist = 1; //Telling the computer to not print the error message
            print_book(lib, total, i+1); //i+1 because it will be used for display not calculation
            
        } 
    } 

    //Handling Error
    if (is_exist == 0) {
        printf("\nSorry, we don't have any book written by %s.\n", p_author);
    }   
    
    transition();

    return 0;

}

int search_by_publisher(char lib[][3][50], int total, char *p_publisher) {
    int i;
    int is_exist = 0; //Same logic

    for (i = 0; i < total; i++) {
        if (compare(lib[i][2], p_publisher)) {

            is_exist = 1;
            print_book(lib, total, i+1);
            
        } 
    } 

    if (is_exist == 0) {
        printf("\nSorry, we don't have any book published by %s\n", p_publisher);
    
    } 

    transition();

    return 0;

}

int print_book(char lib[][3][50], int total, int book_num) {
    //Function to display the result

    int i = 0;

    //Handling Errors
    if (!valid_book_num(book_num, total)) {
        return 0;
    };

    //book_num received is for display. For calculation, it needs to be book_num - 1.
    printf("\n----------- BOOK #%d -----------\n", book_num);
    printf("Title : %s \n", lib[book_num-1][0]);
    printf("Author : %s \n", lib[book_num-1][1]);
    printf("Publisher : %s \n", lib[book_num-1][2]);

    return 0;
}

int add_book(char lib[][3][50], int *p_total) {
    int i = 0;
    char title[50], author[50], publisher[50];
    char confirm = ' ';

    printf("Title : ");
    fgets(title, 50, stdin);

    //IMPORTANT
    //fgets puts \n at the end
    //for "search" options to work, have to change \n to \0 when putting into DB.
    change_buffer(title); 

    printf("Author : ");
    fgets(author, 50, stdin);
    change_buffer(author);

    printf("Publisher : ");
    fgets(publisher, 50, stdin);
    change_buffer(publisher);

    while (confirm != 'Y' && confirm != 'N') {
        printf("Do you want to add this book to Kim's Library? (Y/N)\n");
        scanf("%c", &confirm);
        getchar();

        if (confirm != 'Y' && confirm != 'N') {
            printf("Error: Wrong Command\n");
        }
    }

    if (confirm == 'N') {
            return 0;
        } 

    copy(lib[*p_total][0], title);
    copy(lib[*p_total][1], author);
    copy(lib[*p_total][2], publisher);


    //Add 1 to total
    (*p_total)++;
    
    printf("\nKim's Library now has %d books.\n", *p_total);

    return 0;
}

int rent_book(char lib[][3][50], int *total, char rent[][3][50], int *rent_total) {
    int book_num;
    char confirm = ' ';
    
    available_book_catalog(lib, *total);

    //Allowing user to return to the lobby if there isn't any book available
    if (*total <= 0) {
        transition();
        return 0;
    }

    printf("\nType a book number: ");
    scanf("%d", &book_num);

    while (!valid_book_num(book_num, *total)) {
        printf("\n");
        printf("Type a book number: ");
        scanf("%d", &book_num);
    };

    print_book(lib, *total, book_num);
    getchar();

    do {
        printf("\n");
        printf("Do you want to rent this book? (Y/N)\n");
        printf(": ");
        scanf("%c", &confirm);

    } while (not_y_or_n(confirm));

    if (confirm == 'N') {
            return 0;
        } 

    //Moving a book from library to rented
    copy(rent[*rent_total][0], lib[book_num-1][0]);
    copy(rent[*rent_total][1], lib[book_num-1][1]);
    copy(rent[*rent_total][2], lib[book_num-1][2]);

    //Sort rest of the library, shift 1 section the the left 
    for (; book_num < *total; book_num++) {
        
        copy(lib[book_num-1][0], lib[book_num][0]);
        copy(lib[book_num-1][1], lib[book_num][1]);
        copy(lib[book_num-1][2], lib[book_num][2]);
    }

    (*total)--;
    (*rent_total)++;

    return 0;

}

int return_book(char lib[][3][50], int *total, char rent[][3][50], int *rent_total) {
    int book_num;
    char confirm = ' ';

    rented_book_catalog(rent, *rent_total);

    if (*rent_total <= 0) {
        transition();
        return 0;
    }

    printf("\nType a book number \n");
    printf(": ");
    scanf("%d", &book_num);

    while (!valid_book_num(book_num, *rent_total)) {
        printf("\n");
        printf("Type a book number : ");
        scanf("%d", &book_num);
    };

    print_book(rent, *rent_total, book_num);
    getchar();

    do {
        printf("\n");
        printf("Do you want to return this book? (Y/N)\n");
        printf(": ");
        scanf("%c", &confirm);

    } while (not_y_or_n(confirm));

    if (confirm == 'N') {
            return 0;
        } 
    
    copy(lib[*total][0], rent[book_num-1][0]);
    copy(lib[*total][1], rent[book_num-1][1]);
    copy(lib[*total][2], rent[book_num-1][2]);

    for (; book_num < *rent_total; book_num++) {
        
        copy(rent[book_num-1][0], rent[book_num][0]);
        copy(rent[book_num-1][1], rent[book_num][1]);
        copy(rent[book_num-1][2], rent[book_num][2]);
    }

    (*total)++;
    (*rent_total)--;

    return 0;
}

