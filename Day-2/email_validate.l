%{
#include <stdio.h>
#include <string.h>

char *oldString;
char *newString;

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

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <oldString> <newString>\n", argv[0]);
        return 1;
    }

    oldString = argv[1];
    newString = argv[2];

    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
