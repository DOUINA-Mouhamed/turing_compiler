// variable.c

#include "turing.h"

Variable *variables = NULL;
int var_count = 0;

void add_variable(const char *name, int value)
{
    variables = realloc(variables, (var_count + 1) * sizeof(Variable));
    if (!variables) {
        error_format();
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    strncpy(variables[var_count].name, name, sizeof(variables[var_count].name) - 1);
    variables[var_count].name[sizeof(variables[var_count].name) - 1] = '\0';
    variables[var_count].value = value;
    var_count++;
}

Variable *find_variable(const char *name)
{
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return &variables[i];
        }
    }
    return NULL;
}

void set_variable_value(const char *name, int value, int line_number, const char *line)
{
    Variable *var = find_variable(name);
    if (var) {
        var->value = value;
    } else {
        error_format_line(line_number, line);
        fprintf(stderr, "Error: Variable '%s' not found\n", name);
        exit(1);
    }
}

void declare_variable(const char *name, int value, int line_number, const char *line)
{
    if (find_variable(name)) {
        error_format_line(line_number, line);
        fprintf(stderr, "Error: Variable '%s' already declared\n", name);
        exit(1);
    }
    add_variable(name, value);
}
