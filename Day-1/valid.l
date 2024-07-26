%{
#include <stdio.h>
%}

%%
[6-9][0-9]{9} { printf("Valid mobile number: %s\n", yytext); }
[0-9]+        { printf("Invalid mobile number: %s\n", yytext); }
.             { /* Ignore all other characters */ }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}
