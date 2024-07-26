%{
#include <stdio.h>
#include <stdlib.h>

double operand1 = 0;
double operand2 = 0;
char operator = 0;

void performOperation() {
    double result;
    switch (operator) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 == 0) {
                fprintf(stderr, "Error: Division by zero\n");
                return;
            }
            result = operand1 / operand2;
            break;
        default:
            fprintf(stderr, "Error: Unsupported operator %c\n", operator);
            return;
    }
    printf("Result: %.2f\n", result);
    // Reset the operands and operator for next expression
    operand1 = operand2 = 0;
    operator = 0;
}
%}

%%
[0-9]+(\.[0-9]+)? {
    if (operator == 0) {
        operand1 = atof(yytext);
    } else {
        operand2 = atof(yytext);
        performOperation();
    }
}

[+\-*/] {
    operator = yytext[0];
}

\n {
    // Ignore newlines
}

[ \t] {
    // Ignore whitespace
}

. {
    // Ignore any other characters
}

%%

int main() {
    printf("Enter mathematical expressions (e.g., 3 + 4):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
