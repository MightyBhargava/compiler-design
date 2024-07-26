%{
#include <stdio.h>

void print_tag(const char* tag);
%}

%%

\<[^\>]+\>          { print_tag(yytext); }  // Match HTML tags
.|\n                ;  // Ignore everything else

%%

void print_tag(const char* tag) {
    printf("HTML Tag: %s\n", tag);
}

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
