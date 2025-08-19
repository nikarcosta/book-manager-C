# Book Manager


Book Manager is a simple C program that lets you store, edit, delete, and list books in a local text file.  
It was built as a learning project to practice C programming, working with structs, dynamic memory allocation, and file I/O.

## Features

- Add new books (title, author, price)
- Edit existing books
- Delete books
- List all stored books
- Data is stored in a text file (`data/books.txt`)


## Build & Run

This project uses **CMake**.

# Configure the project
cmake -S . -B build

# Build the executable
cmake --build build

# Run the program
./build/myapp

# Install (optional)

You can also install the program system-wide:
cmake --install build

This will place the executable in /usr/local/bin/myapp and the data file in /usr/local/bin/data/books.txt.

# License

This project is for educational purposes.
Feel free to use or modify it as you wish.