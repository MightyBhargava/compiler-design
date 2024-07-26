#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 100
#define KEYWORDS_COUNT 32

// List of C keywords (a sample list, can be extended)
const char *keywords[KEYWORDS_COUNT] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
    "void", "volatile", "while"
};

// Function to check if a string is a keyword
bool is_keyword(const char *identifier) {
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (strcmp(identifier, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool is_valid_identifier(const char *identifier) {
    // Check if the identifier is not empty
    if (identifier[0] == '\0') {
        return false;
    }

    // Check the first character
    if (!isalpha(identifier[0]) && identifier[0] != '_') {
        return false;
    }

    // Check the remaining characters
    for (int i = 1; identifier[i] != '\0'; i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '_') {
            return false;
        }
    }

    return true;
}

void process_file(FILE *file) {
    char ch;
    char identifier[MAX_IDENTIFIER_LENGTH];
    int index = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == '_') {
            // Start of an identifier
            identifier[index++] = ch;
            while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
                if (index < MAX_IDENTIFIER_LENGTH - 1) {
                    identifier[index++] = ch;
                }
            }
            identifier[index] = '\0'; // Null-terminate the identifier

            // Print or process the identifier
            if (is_keyword(identifier)) {
                printf("'%s' is a keyword.\n", identifier);
            } else if (is_valid_identifier(identifier)) {
                printf("'%s' is a valid identifier.\n", identifier);
            } else {
                printf("'%s' is not a valid identifier.\n", identifier);
            }

            // If the end of file is reached, break the loop
            if (ch == EOF) {
                break;
            }

            // If the character is not part of an identifier, handle it
            if (!isalnum(ch) && ch != '_') {
                ungetc(ch, file); // Put back the character
            }

            // Reset index for the next identifier
            index = 0;
        }
    }
}

int main() {
    FILE *file = fopen("30sample.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    process_file(file);

    fclose(file);
    return 0;
}
