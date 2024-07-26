#include <stdio.h>
#include <ctype.h>

void count_whitespace_and_newline(FILE *file, int *whitespace_count, int *newline_count) {
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) && ch != '\n') {
            (*whitespace_count)++;
        } else if (ch == '\n') {
            (*newline_count)++;
        }
    }
}

int main() {
    FILE *file = fopen("29sample.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int whitespace_count = 0;
    int newline_count = 0;

    count_whitespace_and_newline(file, &whitespace_count, &newline_count);

    fclose(file);

    printf("Number of whitespace characters (excluding newlines): %d\n", whitespace_count);
    printf("Number of newline characters: %d\n", newline_count);

    return 0;
}
