#include <stdio.h>
#include "mainfunc.h"
#include "subfunc.h"
#include "mainfunc.c"
#include "subfunc.c"

int main() {    
    char library[100][3][50];   //Storage for book
    char rented[100][3][50];    //Storage for rented book
    int command = 1;    //User's input (initially set 0 because of while command below)
    int i = 0, j = 0;
    int rent_total= 0, total = 0;

        printf("Welcome to Kim's Library!\n\n");
        printf("Books Available : %d \n", total);
        printf("Books Rented : %d \n", rent_total);
    // Loop to keep the program running
    while (command != 0) {

        //Lobby UI
        
        printf("\nHow can I help you?\n");
        printf("Total Books : %d \n\n", total);

        printf("Exit : 0\n");
        printf("Book Catalog : 1 \n");
        printf("Add book : 2 \n");
        printf("Search book : 3 \n");
        printf("Rent book : 4 \n");
        printf("Return book : 5 \n");
        printf(": ");
        scanf("%d", &command); //get user's input
        getchar();  //getting rid of \0 from the stdin => preventing unintentional input

        switch(command) {  
            case 0:

                printf("Turning Off...\n");
                return 0;
                
            case 1:

                printf("\n");
                book_catalog(library, total, rented, rent_total);
                break;

            case 2:

                printf("\n");
                add_book(library, &total); //Pointer -> adding book changes the total
                break;

            case 3:

                search_menu(library, total);
                break;

            case 4:

                rent_book(library, &total, rented, &rent_total);
                break;

            case 5:

                return_book(library, &total, rented, &rent_total);
                break;

            default:

                printf("Error: Wrong Command\n");
                break;

        }
    
    }
    

    return 0;

}


