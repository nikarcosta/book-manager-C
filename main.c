#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    char title[100];
    char author[50];
    double price;
};

void set_book_data(struct book *b);

void create_file(struct book *books, int n);

int main(void) {

    // struct book book1, book2, book3;
    //
    // set_book_data(&book1);
    // set_book_data(&book2);
    // set_book_data(&book3);
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
        printf("Book %d: \nTitle: %s \nAuthor: %s \nPrice: $%.2lf\n",
            i + 1, books[i].title,
            books[i].author,
            books[i].price );
    }

    create_file(books, n);

    free(books);
    return 0;
}

void set_book_data(struct book *b) {
    printf("Enter the title of the book:\n");
    fgets(b->title, sizeof(b->title), stdin);
    b->title[strcspn(b->title, "\n")] = 0;

    //scanf("%[^\n]", b->title);
    //getchar();

    printf("Enter the author:\n");
    fgets(b->author, sizeof(b->author), stdin);
    b->author[strcspn(b->author, "\n")] = 0;

    //scanf("%[^\n]", b->author);
    //getchar();

    printf("Enter the price of the book:\n");
    scanf("%lf", &b->price);
    getchar();
}

void create_file(struct book *books, int n) {
    FILE *fPtr;
    fPtr = fopen("yourPathHere/books.txt","w");

    if (fPtr == NULL) {
        printf("Unable to create the file!");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(fPtr, "Book %d:\nTitle: %s| Author: %s | Price: %.2lf\n\n",
                i + 1,
                books[i].title,
                books[i].author,
                books[i].price);
    }


    fclose(fPtr);

    printf("File created and saved successfully. :) \n");
}