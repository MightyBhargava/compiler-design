%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

[0-9]+          { printf("Number: %s\n", yytext); }
[a-zA-Z]+       { printf("Word: %s\n", yytext); }
[\t ]+          ; /* Ignore whitespace */
\n              ; /* Ignore newline */
.               ; /* Ignore all other characters */

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
