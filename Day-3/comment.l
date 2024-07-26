%{
#include <stdio.h>

int comment_line_count = 0;
FILE *output_file;
%}

%%

\/\/[^\n]*                { comment_line_count++; }  // Single-line comments
\/\*[^*]*\*+(?:[^/*][^*]*\*+)*\/ { comment_line_count++; }  // Multi-line comments
\n                        { ECHO; }  // New lines
.                         { ECHO; }  // Any other character

%%

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("fopen");
        return 1;
    }

    output_file = fopen(argv[2], "w");
    if (!output_file) {
        perror("fopen");
        fclose(input_file);
        return 1;
    }

    yyin = input_file;
    yyout = output_file;
    yylex();

    fclose(input_file);
    fclose(output_file);

    printf("Number of comment lines: %d\n", comment_line_count);

    return 0;
}

int yywrap() {
    return 1;
}
