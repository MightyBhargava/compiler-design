#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
int E();
int T();
int F();

// Global variables
char* input;
char lookahead;
int errorFlag;

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
        errorFlag = 1;
    }
}

// Function to parse an Expression (E -> T + E | T - E | T)
int E() {
    if (T()) {
        while (lookahead == '+' || lookahead == '-') {
            if (lookahead == '+') {
                match('+');
                if (errorFlag) return 0;
                if (!T()) return 0;
            } else if (lookahead == '-') {
                match('-');
                if (errorFlag) return 0;
                if (!T()) return 0;
            }
        }
        return 1;
    }
    return 0;
}

// Function to parse a Term (T -> F * T | F / T | F)
int T() {
    if (F()) {
        while (lookahead == '*' || lookahead == '/') {
            if (lookahead == '*') {
                match('*');
                if (errorFlag) return 0;
                if (!F()) return 0;
            } else if (lookahead == '/') {
                match('/');
                if (errorFlag) return 0;
                if (!F()) return 0;
            }
        }
        return 1;
    }
    return 0;
}

// Function to parse a Factor (F -> ( E ) | id)
int F() {
    if (lookahead == '(') {
        match('(');
        if (errorFlag) return 0;
        if (!E()) return 0;
        match(')');
        if (errorFlag) return 0;
        return 1;
    } else if (isalpha(lookahead)) {
        match(lookahead);  // match identifier (id)
        if (errorFlag) return 0;
        return 1;
    }
    return 0;
}

// Main function to check the input string against the grammar
int main() {
    char inputStr[100];
    printf("Enter an arithmetic expression: ");
    scanf("%s", inputStr);

    input = inputStr;
    nextChar();
    errorFlag = 0;

    if (E() && lookahead == '\0' && !errorFlag) {
        printf("The input string is valid.\n");
    } else {
        if (!errorFlag) {
            printf("Syntax error: Unexpected character '%c'\n", lookahead);
        }
        printf("The input string is invalid.\n");
    }

    return 0;
}
