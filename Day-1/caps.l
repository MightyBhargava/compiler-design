%{
#include <stdio.h>
%}

%%
[A-Z]+ { printf("Capital word: %s\n", yytext); }
.      { /* Ignore all other characters */ }

%%
int main(int argc, char **argv) {
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}
