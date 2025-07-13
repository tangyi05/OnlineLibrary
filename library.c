#include <stdio.h>

int add_book(char lib[][3][50], int *p_total);
int copy(char *dest, char *copy);
int print_book(char lib[][3][50], int total, int book_num);
int search_title(char lib[][3][50], int total, char *p_title);
int compare(char *arr1, char *arr2);
int change_buffer(char *input);


int main() {    
    char library[100][3][50];   //Storage for book
    int command = 1;    //User's input (initially set 0 because of while command below)
    int i = 0, j = 0, total = 0;

    printf("Welcome to Kim's Library!\n\n");
    printf("Total Books : %d \n", total);

    // Loop to keep the program running
    while (command != 0) {

        printf("\nHow can I help you?\n\n");
        printf("Exit : 0\n")
        printf("Add book: 1 \n");
        printf("View book: 2 \n");
        printf("Search by Title: 3 \n");
        printf("Command : ");
        scanf("%d", &command); //get user's input
        getchar();  //getting rid of \0 from the stdin => preventing unintentional input

        switch(command) {  
            case 0:
                printf("Turning Off...\n");
                return 0;
            case 1:
                printf("\n");
                add_book(library, &total);
                break;
            case 2:
            {
                int book_num;

                printf("\n");
                printf("Type the number of the book: ");
                scanf("%d", &book_num);

                print_book(library, total, book_num);
                break;
            }
        
            case 3:
            {
                printf("\n");
                char title[50];
                printf("What's the title of the book?\n");
                fgets(title, 50, stdin);

                change_buffer(title);
                
                search_title(library, total, title);
                break;
            }
                
                
            default:
                printf("Wrong Command\n");
                break;
        }
    
    }
    

    return 0;

}

int search_title(char lib[][3][50], int total, char *p_title) {
    int i;

    for (i = 0; i < total; i++) {
        if (compare(lib[i][0], p_title)) {
            
            print_book(lib, total, i+1);
            return 0;
        } 
    } 

    printf("\n\"%s\" doesn't exist in our databse.\n", p_title);
    return 0;

}

int print_book(char lib[][3][50], int total, int book_num) {
    int i = 0;

    //Handling Errors
    if (total < book_num && book_num <= 100) {
        printf("\nBook %d is not in our database!\n", book_num);
        return 0;
    } else if (book_num <= 0) {
        printf("\nThat's a wrong number!\n");
        return 0;
    } else if (book_num > 100) {
        printf("\nOur storage can only store 100 books!\n");
        return 0;
    }

    printf("\n------------ BOOK %d -----------------\n", book_num);
    printf("Title : %s \n", lib[book_num-1][0]);
    printf("Author : %s \n", lib[book_num-1][1]);
    printf("Publisher : %s \n", lib[book_num-1][2]);

    return 0;
}

int add_book(char lib[][3][50], int *p_total) {
    int i = 0;
    char title[50], author[50], publisher[50];

    printf("title : ");
    fgets(title, 50, stdin);
    change_buffer(title);

    printf("author : ");
    fgets(author, 50, stdin);
    change_buffer(author);

    printf("publisher : ");
    fgets(publisher, 50, stdin);
    change_buffer(publisher);

    copy(lib[*p_total][0], title);
    copy(lib[*p_total][1], author);
    copy(lib[*p_total][2], publisher);

    (*p_total)++;
    
    printf("\n\nLibrary now has %d books.\n\n", *p_total);

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

        printf("1: %c 2: %c\n", arr1[i], arr2[i]);
        i++;
    }

    return 1;
}

int change_buffer(char *input) {

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
