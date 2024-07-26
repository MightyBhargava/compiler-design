#include <stdio.h>
#include <ctype.h>

void process_operator(char ch) {
    switch (ch) {
        case '+':
            printf("Operator: +\n");
            break;
        case '-':
            printf("Operator: -\n");
            break;
        case '*':
            printf("Operator: *\n");
            break;
        case '/':
            printf("Operator: /\n");
            break;
        default:
            // This function should only process valid operators
            break;
    }
}

void tokenize(FILE *file) {
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        // Check if the character is an operator
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            process_operator(ch);
        }
    }
}

int main() {
    FILE *file = fopen("28sample.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    tokenize(file);

    fclose(file);
    return 0;
}
