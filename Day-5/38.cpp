#include <stdio.h>
#include <ctype.h>

void analyzeFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int ch;
    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;
    int inWord = 0;

    while ((ch = fgetc(file)) != EOF) {
        // Count characters
        charCount++;

        // Count lines
        if (ch == '\n') {
            lineCount++;
        }

        // Count words
        if (isspace(ch) || ch == '\n') {
            if (inWord) {
                wordCount++;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
    }

    // If the file does not end with a space or newline, count the last word
    if (inWord) {
        wordCount++;
    }

    fclose(file);

    printf("Character count: %d\n", charCount);
    printf("Word count: %d\n", wordCount);
    printf("Line count: %d\n", lineCount + 1); // +1 because the last line may not end with \n
}

int main() {
    const char *filename = "38.txt"; // Change this to the name of your file

    analyzeFile(filename);

    return 0;
}
