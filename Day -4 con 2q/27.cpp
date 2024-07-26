#include <stdio.h>

void process_single_line_comment(FILE *file) {
    char ch;
    printf("Single-line comment: ");
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        putchar(ch); // Print comment content
    }
    putchar('\n'); // End of the comment line
}

void process_multi_line_comment(FILE *file) {
    char ch, prev_ch = 0;
    printf("Multi-line comment: ");
    while ((ch = fgetc(file)) != EOF) {
        if (prev_ch == '*' && ch == '/') {
            break;
        }
        putchar(ch); // Print comment content
        prev_ch = ch;
    }
    putchar('\n'); // End of the multi-line comment
}

void tokenize(FILE *file) {
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '/') {
            char next_ch = fgetc(file);
            if (next_ch == '/') {
                process_single_line_comment(file);
            } else if (next_ch == '*') {
                process_multi_line_comment(file);
            } else {
                ungetc(next_ch, file); // Put back character
            }
        }
    }
}

int main() {
    FILE *file = fopen("27sample.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    tokenize(file);

    fclose(file);
    return 0;
}
