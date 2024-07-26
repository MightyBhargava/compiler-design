%{
#include <stdio.h>
#include <stdlib.h>

int isValidDate = 0;

// Function to check if the year is a leap year
int isLeapYear(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

// Function to check if the date is valid
int checkDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return 0; // Year should be in a reasonable range
    if (month < 1 || month > 12) return 0;    // Month should be between 1 and 12
    if (day < 1) return 0;                    // Day should be at least 1

    // Days in each month
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) daysInMonth[1] = 29; // Adjust February for leap years

    if (day > daysInMonth[month - 1]) return 0; // Day should not exceed days in the month

    return 1; // The date is valid
}

%}

%%

([0-9]{2})\/([0-9]{2})\/([0-9]{4}) {
    int day = atoi(yytext);
    int month = atoi(yytext + 3);
    int year = atoi(yytext + 6);

    if (checkDate(day, month, year)) {
        printf("Valid DOB: %s\n", yytext);
        isValidDate = 1;
    } else {
        printf("Invalid DOB: %s\n", yytext);
        isValidDate = 0;
    }
}

.|\n {
    // Ignore any characters that do not match the DOB pattern
}

%%

int main() {
    printf("Enter a DOB to validate (DD/MM/YYYY): ");
    yylex();
    if (!isValidDate) {
        printf("Invalid DOB\n");
    }
    return 0;
}

int yywrap() {
    return 1;
}
