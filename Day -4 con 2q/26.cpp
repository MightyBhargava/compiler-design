#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 100
#define MAX_TOKEN_LENGTH 100

void process_identifier(char *token) {
    // Print or process the identifier token
    printf("Identifier: %s\n", token);
}

void process_constant(char *token) {
    // Print or process the constant token
    printf("Constant: %s\n", token);
}

void process_operator(char *token) {
    // Print or process the operator token
    printf("Operator: %s\n", token);
}

void process_comment(FILE *file) {
    char ch;
    while ((ch = fgetc(file)) != EOF && ch != '\n'); // Skip until end of line
}

void tokenize(FILE *file) {
    char ch;
    char token[MAX_TOKEN_LENGTH];
    int token_index = 0;

    while ((ch = fgetc(file)) != EOF) {
        // Ignore spaces, tabs, and new lines
        if (isspace(ch)) {
            if (token_index > 0) {
                token[token_index] = '\0';
                // Process token
                if (isalpha(token[0])) {
                    process_identifier(token);
                } else if (isdigit(token[0])) {
                    process_constant(token);
                } else {
                    process_operator(token);
                }
                token_index = 0;
            }
            if (ch == '\n') {
                // Optionally handle new lines
            }
        } else if (ch == '/') {
            char next_ch = fgetc(file);
            if (next_ch == '/') {
                // Single-line comment
                process_comment(file);
                continue;
            } else {
                ungetc(next_ch, file); // Put back character
                token[token_index++] = ch;
            }
        } else if (ispunct(ch) && ch != '_') { // Check for operators and punctuations
            if (token_index > 0) {
                token[token_index] = '\0';
                if (isalpha(token[0])) {
                    process_identifier(token);
                } else if (isdigit(token[0])) {
                    process_constant(token);
                } else {
                    process_operator(token);
                }
                token_index = 0;
            }
            token[token_index++] = ch;
            token[token_index] = '\0';
            process_operator(token);
            token_index = 0;
        } else {
            token[token_index++] = ch;
            if (token_index >= MAX_TOKEN_LENGTH - 1) {
                fprintf(stderr, "Token length exceeded.\n");
                token_index = 0;
            }
        }
    }

    if (token_index > 0) {
        token[token_index] = '\0';
        // Process last token
        if (isalpha(token[0])) {
            process_identifier(token);
        } else if (isdigit(token[0])) {
            process_constant(token);
        } else {
            process_operator(token);
        }
    }
}

int main() {
    FILE *file = fopen("26sample.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    tokenize(file);

    fclose(file);
    return 0;
}
