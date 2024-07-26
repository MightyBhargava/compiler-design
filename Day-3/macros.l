%{
#include <stdio.h>

int macro_count = 0;
int header_count = 0;
%}

%%

"#define"[^"\n]*          { macro_count++; }  // Match #define directives
"#include"[^"\n]*         { header_count++; }  // Match #include directives

.|\n                      ;  // Ignore everything else

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

    printf("Number of macros defined: %d\n", macro_count);
    printf("Number of header files included: %d\n", header_count);

    return 0;
}

int yywrap() {
    return 1;
}
