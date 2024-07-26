%{
#include <stdio.h>

// Counters for characters, lines, and words
int char_count = 0;
int line_count = 0;
int word_count = 0;

// Function to handle words
void count_word() {
    word_count++;
}

// Function to handle lines
void count_line() {
    line_count++;
}

%}

%%

// Match a newline character
\n      { 
            count_line(); 
            char_count++; 
         }

// Match any character except newline
.       { 
            char_count++; 
         }

// Match a word (sequence of alphanumeric characters and underscores)
[a-zA-Z0-9_]+ { 
            count_word(); 
         }

// Match multiple spaces, tabs, or newlines
[ \t]+ { /* Ignore whitespace */ }

// Ignore other characters
.      { /* Ignore other characters */ }

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }

    // Set the input stream to the input file
    yyin = input_file;

    // Initialize line count (start at 1 if the file is not empty)
    line_count = 1;

    // Start the lexical analyzer
    yylex();

    // Close the input file
    fclose(input_file);

    // Print the counts
    printf("Number of characters: %d\n", char_count);
    printf("Number of lines: %d\n", line_count);
    printf("Number of words: %d\n", word_count);

    return 0;
}