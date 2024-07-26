%{
#include <stdio.h>
#include <string.h>

char oldString[100];
char newString[100];

void replaceAndPrint(const char *text) {
    const char *pos = text;
    size_t oldLen = strlen(oldString);
    while ((pos = strstr(pos, oldString)) != NULL) {
        // Print part before the match
        fwrite(text, 1, pos - text, stdout);
        // Print the new string
        printf("%s", newString);
        // Move past the old string in the input
        pos += oldLen;
        // Continue from after the old string
        text = pos;
    }
    // Print the remaining part of the text
    printf("%s", text);
}
%}

%%
.* { replaceAndPrint(yytext); }
%%

int main() {
    printf("Enter the old string to be replaced: ");
    scanf("%s", oldString);
    printf("Enter the new string to replace with: ");
    scanf("%s", newString);

    printf("Enter the input string (Ctrl+D to end input):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
