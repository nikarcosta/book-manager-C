#include <stdio.h>
#include <string.h>


void return_to_menu() {
    printf("Press ENTER to return to menu");

    getchar();

    int c;

    do {
        c = getchar();
    } while (c != '\n');
}

bool file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool f_exists = false;
    if (fp != NULL)
    {
        f_exists = true;
        fclose(fp);
    }
    return f_exists;
}