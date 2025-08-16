#ifndef FILE_IO_H
#define FILE_IO_H

#include "book.h"

void set_book_data(struct book *b);

void create_file(struct book *books, int n);

void append_data_to_file(struct book *books, int n);

int load_books(struct book **books_out);

#endif