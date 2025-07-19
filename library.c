#include <stdio.h>
#include <stdlib.h>
#include "mainfunc.h"
#include "subfunc.h"


int main() {    
    BOOK *library;
    int command = 1;    //User's input (initially set 0 because of while command below)
    int i = 0, j = 0;
    int total = 0;
    int borrowed = 0, available = 0;

    library = (BOOK *)malloc(sizeof(BOOK) * 100);

    printf("Welcome to Kim's Library!\n\n");
    // Loop to keep the program running

    while (1) {

        //Lobby UI
        
        printf("\nHow can I help you?\n");
        printf("Total : %d \n", total);
        printf("Available : %d \n", available);
        printf("Borrowed : %d \n\n", borrowed); 

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
                book_catalog(library, total, available, borrowed);
                break;
                
            case 2:
                printf("\n");
                add_book(library, &available); //Pointer -> adding book changes the total
                total = available + borrowed;
                break;

            case 3:
                search_menu(library, available);
                break;

            case 4:
                rent_book(library, total, &available, &borrowed);
                total = available + borrowed;
                break;

            case 5:
                return_book(library, total, &available, &borrowed);
                break;

            default:
                printf("Error: Wrong Command\n");
                break;

        }
    
    }
    

    return 0;

}

