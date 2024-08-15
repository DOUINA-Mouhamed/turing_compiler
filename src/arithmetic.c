// arithmetic.c

#include "turing.h"

int check_arithmetic_operation(const char *line, int line_number)
{
    char var_name[32];
    char operand1[32], operand2[32];
    char operator;

    if (sscanf(line, "%s := %s %c %s", var_name, operand1, &operator, operand2) == 4) {
        Variable *var1 = find_variable(operand1);
        Variable *var2 = find_variable(operand2);

        if (var1 && var2) {
            int result;
            switch (operator) {
                case '+':
                    result = var1->value + var2->value;
                    break;
                case '-':
                    result = var1->value - var2->value;
                    break;
                case '*':
                    result = var1->value * var2->value;
                    break;
                case '/':
                    if (var2->value == 0) {
                        error_format_line(line_number, line);
                        fprintf(stderr, "Error: Division by zero\n");
                        exit(1);
                    }
                    result = var1->value / var2->value;
                    break;
                default:
                    error_format_line(line_number, line);
                    fprintf(stderr, "Error: Unsupported operator '%c'\n", operator);
                    exit(1);
            }
            set_variable_value(var_name, result, line_number, line);
            return 1;
        } else {
            error_format_line(line_number, line);
            fprintf(stderr, "Error: One or both variables in arithmetic operation not found\n");
            exit(1);
        }
    }
    return 0;
}
