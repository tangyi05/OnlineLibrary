#include "mainfunc.h"
#include "subfunc.h"



int book_catalog(BOOK *lib, int total, int available, int borrowed) {
    int option = 0; //User Input to navigate search menu
    int i;

    while (1) {
        
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
                available_book_catalog(lib, total, available);
                transition();
                break;

            case 2: 
                borrowed_book_catalog(lib, total, borrowed);
                transition();
                break;
            
            default: 
                printf("Error: Wrong Command\n"); 
                break;
            }
        }

    return 0;
}

void available_book_catalog(BOOK *lib, int total, int available) {
    int i;

    printf("\n*********** AVAILABLE BOOKS ***********\n");
    if (available == 0) {
        printf("\nWe are currently out of book:(\n");
        return;
    }

    for (i = 0; i < total; i++) {
        if (lib[i].borrowed == 0) {
            printf("\n----------- BOOK #%d -----------\n", i + 1);
            printf("Title : %s \n", lib[i].title);
            printf("Author : %s \n", lib[i].author);
            printf("Publisher : %s \n", lib[i].publisher);
            printf("Borrowed : False \n");
        } else {
            continue;
        }
    }
}

void borrowed_book_catalog(BOOK *lib, int total, int borrowed) {
    printf("\n*********** RENTED BOOKS ***********\n");

    if (borrowed == 0) {
        printf("\nThere isn't any book rented!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        if (lib[i].borrowed == 1) {
            printf("\n----------- BOOK #%d -----------\n", i + 1);
            printf("Title : %s \n", lib[i].title);
            printf("Author : %s \n", lib[i].author);
            printf("Publisher : %s \n", lib[i].publisher);
            printf("Borrowed : True \n");
        }
    }
}

int search_menu(BOOK *lib, int total) {   //Search shouldn't change the value of total, so it shouldn't be a pointer
    int option = 0; //User Input to navigate search menu

    while (1) {
        
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


int search_by_title(BOOK *lib, int total, char *p_title) {
    int i;
    int is_exist = 0;

    for (i = 0; i < total; i++) {
        if (compare(lib[i].title, p_title)) {

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

int search_by_author(BOOK *lib, int total, char *p_author) {
    int i;
    int is_exist = 0; //Handling Error

    for (i = 0; i < total; i++) {
        if (compare(lib[i].author, p_author)) {

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

int search_by_publisher(BOOK *lib, int total, char *p_publisher) {
    int i;
    int is_exist = 0; //Same logic

    for (i = 0; i < total; i++) {
        if (compare(lib[i].publisher, p_publisher)) {

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

int print_book(BOOK *lib, int total, int book_num) {
    //Function to display the result
    int i = 0;

    //Handling Errors
    if (!valid_book_num(book_num, total)) {
        return 0;
    };

    //book_num received is for display. For calculation, it needs to be book_num - 1.
    printf("\n----------- BOOK #%d -----------\n", book_num);
    printf("Title : %s \n", lib[book_num-1].title);
    printf("Author : %s \n", lib[book_num-1].author);
    printf("Publisher : %s \n", lib[book_num-1].publisher);
    if ((lib[book_num-1].borrowed) == 1) {
        printf("Borrowed : True \n");
    } else {
        printf("Borrowed : False \n");
    }
    


    return 0;
}

int add_book(BOOK *lib, int *available) {
    int i = 0;
    char title[50], author[50], publisher[50];
    BOOK new_book;
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

    copy(new_book.title, title);
    copy(new_book.author, author);
    copy(new_book.publisher, publisher);
    new_book.borrowed = 0;

    lib[*available] = new_book;

    //Add 1 to total
    (*available)++;
    
    printf("\nKim's Library now has %d books.\n", *available);

    return 0;
}

int rent_book(BOOK *lib, int total, int *available, int *borrowed) {
    int book_num;
    char confirm = ' ';
    
    available_book_catalog(lib, total, *available);

    //Allowing user to return to the lobby if there isn't any book available
    if (*available <= 0) {
        transition();
        return 0;
    }

    printf("\nType a book number: ");
    scanf("%d", &book_num);

    while (!valid_book_num(book_num, total) || lib[book_num-1].borrowed == 1) {
        if (lib[book_num-1].borrowed == 1) {
            printf("\nThat book is currently not available:(\n");
        }

        printf("\nType a book number: ");
        scanf("%d", &book_num);        
    }


    print_book(lib, total, book_num);
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

    lib[book_num-1].borrowed = 1;

    (*available)--;
    (*borrowed)++;

    return 0;

}

int return_book(BOOK *lib, int total, int *available, int *borrowed) {
    int book_num;
    char confirm = ' ';

    borrowed_book_catalog(lib, total, *borrowed);

    if (*borrowed <= 0) {
        transition();
        return 0;
    }

    printf("\nType a book number : ");
    scanf("%d", &book_num);

    while (!valid_book_num(book_num, total) || lib[book_num-1].borrowed == 0) {
        if (lib[book_num-1].borrowed == 0) {
            printf("\nThat book is already in the library:(\n");
        }

        printf("\nType a book number: ");
        scanf("%d", &book_num);        
    }


    print_book(lib, total, book_num);
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
    
    lib[book_num-1].borrowed = 0;

    (*available)++;
    (*borrowed)--;

    return 0;
}