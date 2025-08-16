#include <stdio.h>
#include "../include/book.h"

int main(void) {
    int option;
    int run = 1;

    while (run) {

        printf("\n ____              _      __  __ ");
        printf("\n|  _ \\            | |    |  \\/  |");
        printf("\n| |_) | ___   ___ | | __ | \\  / | __ _ _ __   __ _  __ _  ___ _ __ ");
        printf("\n|  _ < / _ \\ / _ \\| |/ / | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|");
        printf("\n| |_) | (_) | (_) |   <  | |  | | (_| | | | | (_| | (_| |  __/ |");
        printf("\n|____/ \\___/ \\___/|_|\\_\\ |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|");
        printf("\n                                                    __/ |");
        printf("\n                                                   |___/");


        printf("\nWelcome To Your Book Manager!\n");
        printf("Enter the number corresponding to one of the options below to continue: \n");
        printf("1 - Add book;\n");
        printf("2 - Delete book;\n");
        printf("3 - View books;\n");
        printf("4 - Edit book;\n");
        printf("0 - Exit the application;\n");

        scanf("%d", &option);

        switch (option) {
            case 1:
                add_book();
                break;
            case 2:
                delete_book();
                break;
            case 3:
                view_books();
                break;
            case 4:
                edit_book();
                break;
            case 0:
                run = 0;
                break;
            default:
                printf("Enter a valid option!");

        }
    }

    return 0;
}

