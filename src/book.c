#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/book.h"
#include "../include/file_io.h"
#include "../include/utils.h"
#include "config.h"

void add_book() {
    printf("*******************************************************************\n");
    printf("****************************ADD BOOKS******************************\n");
    printf("*******************************************************************\n");
    int n;
    printf("How many books?\n");
    scanf("%d", &n);
    getchar();

    struct book *books = malloc(sizeof(struct book) * n);

    for (int i = 0; i < n; i++) {
        printf("Enter data for book %d\n", i + 1);
        set_book_data(&books[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("Book: \nTitle: %s \nAuthor: %s \nPrice: $%.2lf\n",
            books[i].title,
            books[i].author,
            books[i].price );
    }

    if (file_exists(BOOKS_FILE)) {
        append_data_to_file(books, n);
    } else {
        create_file(books, n);
    }


    free(books);

    return_to_menu();
}

void view_books() {
    printf("*******************************************************************\n");
    printf("****************************VIEW BOOKS*****************************\n");
    printf("*******************************************************************\n");
    FILE *fPtr;
    char ch;

    printf("Trying to open file: %s\n", BOOKS_FILE);
    fPtr = fopen(BOOKS_FILE, "r");

    if (fPtr == NULL) {
        printf("Unable to open file.\n");
        printf("Please check whether file exists and you have reading privileges.\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        ch = fgetc(fPtr);

        putchar(ch);

    } while(ch != EOF);

    fclose(fPtr);

    return_to_menu();

}

void delete_book() {
    printf("*********************************************************************\n");
    printf("****************************DELETE BOOKS*****************************\n");
    printf("*********************************************************************\n");
    getchar();
    printf("Enter the title of the book you want to delete: \n");
    char book_title_to_delete[256];
    fgets(book_title_to_delete, sizeof(book_title_to_delete),stdin);
    book_title_to_delete[strcspn(book_title_to_delete, "\n")] = '\0';

    struct book *my_books = NULL;
    int total_books = load_books(&my_books);

    bool book_found = false;

    for (int i = 0; i < total_books; i++) {
        if (strcmp(my_books[i].title, book_title_to_delete) == 0) {
            for (int j = i; j < total_books - 1; j++ ) {
                my_books[j] = my_books[j+1];
            }

            total_books--;
            book_found = true;
            break;
        }
    }

    if (book_found) {
        create_file(my_books, total_books);

        printf("Book deleted successfully!\n");
    } else {
        printf("Book not found!\n");
    }

    free(my_books);
    return_to_menu();
}

void edit_book() {
    printf("*********************************************************************\n");
    printf("****************************EDIT BOOKS*******************************\n");
    printf("*********************************************************************\n");
    getchar();

    printf("Enter the title of the book you want to edit: \n");
    char book_to_edit[256];
    fgets(book_to_edit, sizeof(book_to_edit),stdin);
    book_to_edit[strcspn(book_to_edit, "\n")] = '\0';

    struct book *my_books = NULL;
    int total_books = load_books(&my_books);

    bool book_found = false;

    printf("What do you want to edit? Type the number correspoding to the option.\n");
    printf("1 - Book Title\n");
    printf("2 - Book Author\n");
    printf("3 - Book Price\n");

    int edit_option;
    scanf("%d", &edit_option);
    getchar();

    char title[100];
    char author[50];
    double price;

    switch (edit_option) {
        case 1:
            printf("Enter new title:\n");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0';
            break;
        case 2:
            printf("Enter new author:\n");
            fgets(author, sizeof(author), stdin);
            author[strcspn(author, "\n")] = '\0';
            break;
        case 3:
            printf("Enter new price:\n");
            scanf("%lf", &price);
            break;
        default:
            printf("Invalid option!");
            return_to_menu();
            return;
    }

    for (int i = 0; i < total_books; i++) {
        if (strcmp(my_books[i].title, book_to_edit) == 0) {
            book_found = true;

            if (edit_option == 1) {
                strcpy(my_books[i].title, title);
            } else if (edit_option == 2) {
                strcpy(my_books[i].author, author);
            } else {
                my_books[i].price = price;
            }
            break;
        }

    }

    if (book_found) {
        create_file(my_books, total_books);

        printf("Book edited successfully!\n");
    } else {
        printf("Book not found!\n");
    }

    free(my_books);
    return_to_menu();
}



