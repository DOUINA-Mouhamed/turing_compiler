// put.c

#include "turing.h"

void interpret_put_command(const char *line, int line_number)
{
    if (strncmp(line, "put ", 4) == 0) {
        const char *start = strchr(line, '"');
        const char *end = strrchr(line, '"');
        if (start && end && start != end) {
            printf("%.*s\n", (int)(end - start - 1), start + 1);
        } else {
            error_format_line(line_number, line);
            fprintf(stderr, "Error: Invalid string format.\n");
            exit(1);
        }
    }
}

void put_variable(const char *line, int line_number)
{
    char var_name[32];

    if (sscanf(line, "put %s", var_name) == 1) {
        Variable *var = find_variable(var_name);
        if (var) {
            printf("%d\n", var->value);
        } else {
            error_format_line(line_number, line);
            fprintf(stderr, "Error: Variable '%s' not found\n", var_name);
            exit(1);
        }
    } else {
        error_format_line(line_number, line);
        fprintf(stderr, "Error: Invalid put command for variable\n");
        exit(1);
    }
}
