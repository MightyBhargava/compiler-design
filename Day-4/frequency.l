%{
#include <stdio.h>
#include <string.h>

char word[100];
int count = 0;
%}

%%

[a-zA-Z]+ {
    if (strcmp(yytext, word) == 0) {
        count++;
    }
}

\n { 
    // End of input 
    return 0; 
}

. { 
    // Ignore other characters 
}

%%

int main(int argc, char *argv[]) {
    
    strcpy(word, argv[1]);
    printf("Enter a sentence: ");
    yylex();
    printf("The word '%s' occurs %d times.\n", word, count);
    return 0;
}

int yywrap() {
    return 1;
}
