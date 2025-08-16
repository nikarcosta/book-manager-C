#ifndef BOOK_H
#define BOOK_H

extern const char *FILENAME;

struct book {
    char title[100];
    char author[50];
    double price;
};

void add_book();

void view_books();

void delete_book();

void edit_book();

#endif