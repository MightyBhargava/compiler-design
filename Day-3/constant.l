%{
#include <stdio.h>

void print_constant(const char* constant) {
    printf("Constant: %s\n", constant);
}
%}

%%

\/\/[^\n]*                           ;  // Ignore single line comments
\/\*([^*]|\*+[^/*])*\*+\/            ;  // Ignore multi-line comments
[ \t\n]+                             ;  // Ignore whitespace

\"(\\.|[^\\"])*\"                    { print_constant(yytext); }  // String literal
\'(\\.|[^\\\'])\'                    { print_constant(yytext); }  // Character constant
[0-9]+                               { print_constant(yytext); }  // Integer constant
[0-9]+\.[0-9]*([eE][-+]?[0-9]+)?     { print_constant(yytext); }  // Floating-point constant with optional exponent
\.[0-9]+([eE][-+]?[0-9]+)?           { print_constant(yytext); }  // Floating-point constant starting with a dot
[0-9]+[eE][-+]?[0-9]+                { print_constant(yytext); }  // Floating-point constant with exponent only

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
