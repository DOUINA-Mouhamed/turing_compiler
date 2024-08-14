#include "turing.h"

void remove_comment(char *line)
{
    char *comment_start = strchr(line, '%');

    if (comment_start) {
        *comment_start = '\0';
    }

    char *bracket_start = strstr(line, "/*");
    while (bracket_start) {
        char *bracket_end = strstr(bracket_start, "*/");
        if (bracket_end) {
            memmove(bracket_start, bracket_end + 2, strlen(bracket_end + 2) + 1);
        } else {
            *bracket_start = '\0';
            break;
        }
        bracket_start = strstr(line, "/*");
    }
}

int is_blank_line(const char *line)
{
    while (*line != '\0') {
        if (!isspace((unsigned char)*line)) {
            return 0;
        }
        line++;
    }
    return 1;
}

void handle_comment_blocks(char *line, int *in_comment)
{
    if (*in_comment) {
        char *bracket_end = strstr(line, "*/");
        if (bracket_end) {
            *in_comment = 0;
            memmove(line, bracket_end + 2, strlen(bracket_end + 2) + 1);
        } else {
            *line = '\0';
        }
    }

    char *bracket_start = strstr(line, "/*");
    if (bracket_start) {
        char *bracket_end = strstr(bracket_start, "*/");
        if (bracket_end) {
            memmove(bracket_start, bracket_end + 2, strlen(bracket_end + 2) + 1);
        } else {
            *bracket_start = '\0';
            *in_comment = 1;
        }
    }

    remove_comment(line);
}

void process_line(char *line, int line_number)
{
    if (strncmp(line, "var ", 4) == 0) {
        parse_declaration(line, line_number);
    } else if (strstr(line, ":=") != NULL) {
        char temp_line[256];
        strncpy(temp_line, line, sizeof(temp_line) - 1);
        temp_line[sizeof(temp_line) - 1] = '\0';
        remove_comment(temp_line);  // Remove any inline comments
        parse_assignment(temp_line, line_number);
    } else if (strncmp(line, "put ", 4) == 0) {
        if (strchr(line, '"')) {
            interpret_put_command(line, line_number);
        } else {
            put_variable(line, line_number);
        }
    } else {
        error_format_line(line_number, line);
        fprintf(stderr, "Error: Unsupported command\n");
        exit(1);
    }
}

void parse_turing_file(FILE *file)
{
    char line[256];
    int line_number = 0;
    int in_comment = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;
        handle_comment_blocks(line, &in_comment);

        if (in_comment || is_blank_line(line)) {
            continue;
        }

        process_line(line, line_number);
    }
}

void parse_declaration(const char *line, int line_number)
{
    char var_names[256];
    char *token;
    const char delimiters[] = " ,";

    if (sscanf(line, "var %[^:]: int", var_names) == 1) {
        token = strtok(var_names, delimiters);
        while (token != NULL) {
            declare_variable(token, 0, line_number, line);
            token = strtok(NULL, delimiters);
        }
    } else {
        error_format_line(line_number, line);
        fprintf(stderr, "Error: Invalid variable declaration\n");
        exit(1);
    }
}

void parse_assignment(const char *line, int line_number)
{
    char var_name[32];
    int value;

    if (check_arithmetic_operation(line, line_number)) {
        return;
    }

    if (sscanf(line, "%s := %d", var_name, &value) == 2) {
        set_variable_value(var_name, value, line_number, line);
        return;
    }

    error_format_line(line_number, line);
    fprintf(stderr, "Error: Invalid assignment statement\n");
    exit(1);
}
