#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *FILENAME = "";

struct book {
    char title[100];
    char author[50];
    double price;
};

void set_book_data(struct book *b);

void create_file(struct book *books, int n);

void append_data_to_file(struct book *books, int n);

bool file_exists(const char *filename);

int main(void) {
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

    if (file_exists(FILENAME)) {
        append_data_to_file(books, n);
    } else {
        create_file(books, n);
    }


    free(books);
    return 0;
}

bool file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp);
    }
    return is_exist;
}

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
    fPtr = fopen(FILENAME,"w");

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

void append_data_to_file(struct book *books, int n) {
    FILE *fPtr;
    fPtr = fopen(FILENAME,"a");

    if (fPtr == NULL) {
        printf("\nUnable to open the file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
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

    printf("New data appended to file and saved successfully. :) \n");

}