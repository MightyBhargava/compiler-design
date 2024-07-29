#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Function prototypes
double expression();
double term();
double factor();
double exponent();
void nextChar();
void match(char expected);

// Global variables
char* input;
char lookahead;

// Function to get the next character
void nextChar() {
    lookahead = *input++;
}

// Function to match the current character and move to the next
void match(char expected) {
    if (lookahead == expected) {
        nextChar();
    } else {
        printf("Syntax error: Expected '%c', found '%c'\n", expected, lookahead);
        exit(1);
    }
}

// Function to parse an Expression (E -> T {+ T | - T})
double expression() {
    double result = term();
    while (lookahead == '+' || lookahead == '-') {
        if (lookahead == '+') {
            match('+');
            result += term();
        } else if (lookahead == '-') {
            match('-');
            result -= term();
        }
    }
    return result;
}

// Function to parse a Term (T -> F {* F | / F})
double term() {
    double result = factor();
    while (lookahead == '*' || lookahead == '/') {
        if (lookahead == '*') {
            match('*');
            result *= factor();
        } else if (lookahead == '/') {
            match('/');
            result /= factor();
        }
    }
    return result;
}

// Function to parse a Factor (F -> E ^ F | ( E ) | number)
double factor() {
    double result;
    if (lookahead == '(') {
        match('(');
        result = expression();
        match(')');
    } else if (isdigit(lookahead) || lookahead == '.') {
        char number[20];
        int i = 0;
        while (isdigit(lookahead) || lookahead == '.') {
            number[i++] = lookahead;
            nextChar();
        }
        number[i] = '\0';
        result = atof(number);
    } else {
        printf("Syntax error: Unexpected character '%c'\n", lookahead);
        exit(1);
    }
    return result;
}

// Function to parse an Exponentiation (E -> F ^ E)
double exponent() {
    double result = factor();
    if (lookahead == '^') {
        match('^');
        result = pow(result, exponent());
    }
    return result;
}

// Main function to evaluate the input expression
int main() {
    char inputStr[100];
    printf("Enter an arithmetic expression: ");
    scanf("%s", inputStr);

    input = inputStr;
    nextChar();

    double result = expression();
    if (lookahead == '\0') {
        printf("The result of the expression is: %.2f\n", result);
    } else {
        printf("Syntax error: Unexpected character '%c'\n", lookahead);
    }

    return 0;
}
