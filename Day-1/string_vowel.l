%{
#include <stdio.h>
%}

/* Rules Section */
%%
[aeiouAEIOU][a-zA-Z]*   { printf("Accepted: %s\n", yytext); }
.                       ; /* Ignore all other characters */

%%

/* User Code Section */
int main(int argc, char **argv) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
