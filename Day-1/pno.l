%{
#include <stdio.h>
int positive_count = 0;
int negative_count = 0;
%}

%%

[+-]?[0-9]+(\.[0-9]+)?    {
                            double num = atof(yytext);
                            if (num > 0) {
                                positive_count++;
                                printf("Positive number: %s\n", yytext);
                            } else if (num < 0) {
                                negative_count++;
                                printf("Negative number: %s\n", yytext);
                            }
                        }
.                         ; /* Ignore all other characters */

%%

int main(int argc, char **argv) {
    yylex();
    printf("Total positive numbers: %d\n", positive_count);
    printf("Total negative numbers: %d\n", negative_count);
    return 0;
}

int yywrap() {
    return 1;
}
