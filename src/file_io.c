#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/book.h"
#include "../include/config.h"

void set_book_data(struct book *b) {
    printf("Enter the title of the book:\n");
    fgets(b->title, sizeof(b->title), stdin);
    b->title[strcspn(b->title, "\n")] = 0;

    printf("Enter the author:\n");
    fgets(b->author, sizeof(b->author), stdin);
    b->author[strcspn(b->author, "\n")] = 0;

    printf("Enter the price of the book:\n");
    scanf("%lf", &b->price);
    getchar();
}

void create_file(struct book *books, int n) {
    FILE *fPtr;
    fPtr = fopen(BOOKS_FILE,"w");

    if (fPtr == NULL) {
        printf("Unable to create the file!");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(fPtr, "Book:\nTitle: %s| Author: %s | Price: %.2lf\n\n",
                books[i].title,
                books[i].author,
                books[i].price);
    }

    fclose(fPtr);

    printf("File created and saved successfully. :) \n");
}


void append_data_to_file(struct book *books, int n) {
    FILE *fPtr;
    fPtr = fopen(BOOKS_FILE,"a");

    if (fPtr == NULL) {
        printf("\nUnable to open the file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(fPtr, "Book:\nTitle: %s| Author: %s | Price: %.2lf\n\n",
                books[i].title,
                books[i].author,
                books[i].price);
    }

    fclose(fPtr);

    printf("New data appended to file and saved successfully. :) \n");

}

int load_books(struct book **books_out) {
    FILE *fPtr = fopen(BOOKS_FILE, "r");
    if (fPtr == NULL) {
        printf("Could not open file for reading.\n");
        return 0;
    }

    int capacity = 10;
    int count = 0;
    struct book *books = malloc(capacity * sizeof(struct book));

    char line[256];
    while (fgets(line, sizeof(line), fPtr)) {
        // Skip "Book N:" line
        if (strncmp(line, "Book", 4) == 0) {
            if (!fgets(line, sizeof(line), fPtr)) break;

            if (count >= capacity) {
                capacity *= 2;
                books = realloc(books, capacity * sizeof(struct book));
            }

            char *title_start = strstr(line, "Title: ");
            char *author_start = strstr(line, "Author: ");
            char *price_start = strstr(line, "Price: ");

            if (title_start && author_start && price_start) {
                sscanf(title_start, "Title: %[^|]| Author: %[^|]| Price: %lf",
                       books[count].title,
                       books[count].author,
                       &books[count].price);
                count++;
            }
        }
    }

    fclose(fPtr);
    *books_out = books;
    return count;
}