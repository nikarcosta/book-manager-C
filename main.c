#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *FILENAME = "/home/monique/CLionProjects/untitled/books.txt";

struct book {
    char title[100];
    char author[50];
    double price;
};

void set_book_data(struct book *b);

void create_file(struct book *books, int n);

void append_data_to_file(struct book *books, int n);

bool file_exists(const char *filename);

void add_book();

void view_books();

void delete_book();

void edit_book();

int load_books(struct book **books_out);

void return_to_menu();

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
            case 0:
                run = 0;
                break;
            default:
                printf("Enter a valid option!");

        }
    }

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
    fPtr = fopen(FILENAME,"a");

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

    if (file_exists(FILENAME)) {
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

    fPtr = fopen(FILENAME, "r");

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

    struct book *my_books = NULL;
    int total_books = load_books(&my_books);

    total_books--;
    bool book_found = false;

    for (int i = 0; i < total_books; i++) {
        if (my_books->author == book_title_to_delete) {
            *my_books[i].title = *my_books[i+1].title;
            *my_books[i].author = *my_books[i + 1].author;
            my_books[i].price = my_books[i+1].price;

            book_found = true;
        }
    }

    if (book_found) {
        create_file(my_books, total_books);

        printf("Book deleted successfully!\n");
    } else {
        printf("Book not found!\n");
    }

    return_to_menu();
}

void edit_book(){}

int load_books(struct book **books_out) {
    FILE *fPtr = fopen(FILENAME, "r");
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

void return_to_menu() {
    printf("Press ENTER to return to menu");

    getchar();

    int c;

    do {
        c = getchar();
    } while (c != '\n');
}