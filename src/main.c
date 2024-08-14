// main.c

#include "turing.h"

int main(int argc, char *argv[])
{
    FILE *file;

    error_handling(argc, argv, &file);

    parse_turing_file(file);

    fclose(file);
    return 0;
}
