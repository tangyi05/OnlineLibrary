#include <stdio.h>
#include "subfunc.h"


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

int not_y_or_n(char answer) {

    if (answer != 'Y' && answer != 'N') {
        printf("confirm : %c", answer);
        printf("\nError: Wrong Command\n");
        return 1;
    }
    
    return 0; 

}