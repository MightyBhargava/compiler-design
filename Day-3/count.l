%{
#include <stdio.h>
#include <ctype.h>

int char_count = 0;
int line_count = 0;
int word_count = 0;
int in_word = 0;

void count_word() {
    if (in_word) {
        word_count++;
        in_word = 0;
    }
}

int yywrap(void) {
    return 1;
}
%}

%x COMMENT

%%

\/\/[^\n]*             { char_count += yyleng; }  // Single line comment
\/\*                   { BEGIN(COMMENT); char_count += 2; }  // Start multi-line comment
<COMMENT>[^*]*\*+([^/*][^*]*\*+)*\/  { char_count += yyleng; BEGIN(INITIAL); }  // End multi-line comment
<COMMENT>.|\n          { char_count += yyleng; if (*yytext == '\n') line_count++; }  // Handle new lines in comments

[ \t]+                 { char_count += yyleng; }  // Ignore spaces and tabs
\n                     { char_count += yyleng; line_count++; count_word(); }  // New lines

[a-zA-Z_][a-zA-Z0-9_]* { char_count += yyleng; word_count++; }  // Identifiers
[0-9]+                 { char_count += yyleng; word_count++; }  // Numbers
.                      { char_count += yyleng; }  // Any other character

%%

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("fopen");
        return 1;
    }

    yyin = input_file;
    yylex();

    fclose(input_file);

    printf("Number of characters: %d\n", char_count);
    printf("Number of lines: %d\n", line_count);
    printf("Number of words: %d\n", word_count);

    return 0;
}
