%{
#include <stdio.h>

int vowel_count = 0;
int consonant_count = 0;
%}

%%
[aAeEiIoOuU] {
    vowel_count++;
}
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] {
    consonant_count++;
}

. {
    /* Ignore all other characters */
}
%%

int main(int argc, char **argv) {
    printf("Enter a sentence: ");
    yylex();
    printf("Number of vowels: %d\n", vowel_count);
    printf("Number of consonants: %d\n", consonant_count);
    return 0;
}
int yywrap() {
    return 1;
}
