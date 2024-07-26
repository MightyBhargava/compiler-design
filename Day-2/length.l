%{
#include <stdio.h>
#include <string.h>

int maxLength = 0;
int currentLength = 0;
%}

%%

[^\n\t\r ]+ {
    currentLength = yyleng;
    if (currentLength > maxLength) {
        maxLength = currentLength;
    }
}

[\n\t\r ]+ {
    // Ignore whitespace characters
}

%%

int main() {
    yylex();
    printf("The length of the longest word is: %d\n", maxLength);
    return 0;
}

int yywrap() {
    return 1;
}
