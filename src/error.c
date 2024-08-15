// error.c

#include "turing.h"

void error_format(void)
{
    printf("\033[0;31m");
    printf("/!\\\n");
    printf("\033[0m");
}

void error_format_line(int line_number, const char *error_line)
{
    printf("\033[0;31m");
    printf("/!\\ Error at line %d:\n", line_number);
    printf("%s\n", error_line);
    printf("\033[0m");
}

void arg_error(int argc)
{
    if (argc != 2) {
        error_format();
        fprintf(stderr, "Usage: %s <sourcefile.turing>\n", "./turing");
        exit(1);
    }
}

void file_error(char *file_name[], FILE **file)
{
    *file = fopen(file_name[1], "r");
    if (!*file) {
        error_format();
        fprintf(stderr, "Error: Could not open file %s\n", file_name[1]);
        exit(1);
    }
}

void error_handling(int argc, char *argv[], FILE **file)
{
    arg_error(argc);
    file_error(argv, file);
}
