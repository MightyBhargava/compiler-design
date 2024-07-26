%{
#include <stdio.h>

// Function to print token type and value
void print_token(const char *type, const char *value);
%}

// Define token types
%option noyywrap

%%

"int"|"void"|"return"|"include"|"main"   { print_token("Keyword", yytext); }
"#[ \t]*include[ \t]*<[^>]+>"             { print_token("Preprocessor Directive", yytext); }
"#[ \t]*include[ \t]*\"[^\"]*\""         { print_token("Preprocessor Directive", yytext); }
"\"[^\"]*\""                             { print_token("String Literal", yytext); }
[0-9]+                                  { print_token("Integer Literal", yytext); }
[+-/*=<>!]+                              { print_token("Operator", yytext); }
[ \t\n]+                                { /* Ignore whitespace */ }
[a-zA-Z_][a-zA-Z0-9_]*                   { print_token("Identifier", yytext); }
"(" | "{" | "}" | "[" | "]" | "." | "," | ";" { print_token("Punctuation", yytext); }
.                                       { print_token("Unknown", yytext); }

%%

void print_token(const char *type, const char *value) {
    printf("%s: %s\n", type, value);
}

int main(int argc, char **argv) {
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
