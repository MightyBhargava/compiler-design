%{
#include <stdio.h>
%}

%%

[a-zA-Z]+ {
    printf("Word: %s\n", yytext);
}

"=="|"!="|"<="|">="|"<"|">"|">!" {
    printf("Relational Operator: %s\n", yytext);
}

.|\n {
    // Ignore any characters that do not match words or relational operators
}

%%

int main() {
    printf("Enter text to analyze: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
