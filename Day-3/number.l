%{
#include <stdio.h>

int line_number = 1;
%}

%%

.*\n   { printf("%d: %s", line_number++, yytext); }  // Match each line and print with line number

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

    return 0;
}

int yywrap() {
    return 1;
}
