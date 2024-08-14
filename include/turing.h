#ifndef TURING_H
#define TURING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
#include <Windows.h>
#endif

typedef struct {
    char name[32];
    int value;
} Variable;

/* variable.c */
void add_variable(const char *name, int value);
Variable *find_variable(const char *name);
void set_variable_value(const char *name, int value, int line_number, const char *line);
void declare_variable(const char *name, int value, int line_number, const char *line);

/* arithmetic.c */
int check_arithmetic_operation(const char *line, int line_number);

/* parser.c */
void parse_turing_file(FILE *file);
void parse_declaration(const char *line, int line_number);
void parse_assignment(const char *line, int line_number);

/* put.c */
void interpret_put_command(const char *line, int line_number);
void put_variable(const char *line, int line_number);

/* error.c */
void error_format(void);
void error_format_line(int line_number, const char *error_line);
void arg_error(int argc);
void file_error(char *file_name[], FILE **file);
void error_handling(int argc, char *argv[], FILE **file);

#endif /* TURING_H */
