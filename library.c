#include <stdio.h>

int book_catalog(char lib[][3][50], int total, char rent_lib[][3][50], int rent_total);
int available_book_catalog(char lib[][3][50], int total);
int rented_book_catalog(char rent_lib[][3][50], int rent_total);

int add_book(char lib[][3][50], int *p_total);
int print_book(char lib[][3][50], int total, int book_num);
int search_menu(char lib[][3][50], int total);
int search_by_title(char lib[][3][50], int total, char *p_title);
int search_by_publisher(char lib[][3][50], int total, char *p_publisher);
int search_by_author(char lib[][3][50], int total, char *p_author);
int rent_book(char lib[][3][50], int *total, char rent[][3][50], int *rent_total);

int transition();
int copy(char *dest, char *copy);
int compare(char *arr1, char *arr2);
int change_buffer(char *input);
int valid_book_num(int book_num, int total);

int main() {    
    char library[100][3][50];   //Storage for book
    char rented[100][3][50];    //Storage for rented book
    int command = 1;    //User's input (initially set 0 because of while command below)
    int i = 0, j = 0;
    int rent_total= 0, total = 0;

        printf("Welcome to Kim's Library!\n\n");
        printf("Total Books : %d \n", total);
    // Loop to keep the program running
    while (command != 0) {

        //Lobby UI
        
        printf("\nHow can I help you?\n");
        printf("Total Books : %d \n\n", total);

        printf("Exit : 0\n");
        printf("Available Book Catalog: 1 \n");
        printf("Add book: 2 \n");
        printf("Search book: 3 \n");
        printf("Rent book: 4 \n");
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

            default:

                printf("Error: Wrong Command\n");
                break;

        }
    
    }
    

    return 0;

}

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
    int book_num = -1;
    char confirm = ' ';
    printf("\n");
    printf("Type a book number: ");
    scanf("%d", &book_num);

    while (!valid_book_num(book_num, *total)) {
        printf("\n");
        printf("Type a book number: ");
        scanf("%d", &book_num);
    };

    print_book(lib, *total, book_num);
    getchar();

    //이거 Y/N 리턴하는거 함수로 바꾸기
    while (confirm != 'Y' && confirm != 'N') {
        printf("\n");
        printf("Do you want to rent this book? (Y/N)\n");
        printf(": ");
        scanf("%c", &confirm);

        if (confirm != 'Y' && confirm != 'N') {
            printf("confirm : %c", confirm);
            printf("Error: Wrong Command\n");
        }
    }

    if (confirm == 'N') {
            return 0;
        } 
    // 여기까지 바꿀 수 있을듯

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


//**MINOR FUNCTIONS (Handling string, buffer)

int transition() {
    char any_key[2];
    printf("\n");
    printf("<Press Enter>");
    scanf("%c", &any_key[0]);

    return 0;
}

int copy(char *dest, char *copy) {

    int i = 0;

    while (copy[i]) {
        dest[i] = copy[i];
        i++;
    }

    dest[i] = '\0';

    return 0;

}

int compare(char *arr1, char *arr2) {
    int i = 0;

    while (arr1[i] || arr2[i]) {
        if (!arr1[i] || !arr2[i]) {
            return 0;
        }
        
        if (arr1[i] != arr2[i]) {
            return 0;
        }

        i++;
    }

    return 1;
}


int valid_book_num(int book_num, int total) {

    if (total < book_num && book_num <= 100) {

        //Not out of range, but doesn't exist
        printf("\nBook %d is not in our database!\n", book_num);
        return 0;

    } else if (book_num <= 0) {

        //Out of range
        printf("\nThat's a wrong number!\n");
        return 0;

    } else if (book_num > 100) {

        //Out of range
        printf("\nOur storage can only store 100 books!\n");
        return 0;

    }

    return 1;
}

int change_buffer(char *input) {

    //Function for handling \n that gets automatically added to fgets() command.
    //Turns \n -> \0 : preventing line switch
    
    int i = 0;

    while (input[i] != '\0') {
        if (input[i] == '\n') {
            input[i] = '\0';  // Replace newline with null terminator
            break;
        }
        i++;
    }
    return 0;
}
