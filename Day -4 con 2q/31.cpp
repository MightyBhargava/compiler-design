#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_RULE_LENGTH 100

// Function prototypes
void eliminate_left_recursion(char rules[MAX_RULES][MAX_RULE_LENGTH], int rule_count);

int main() {
    int rule_count;
    char rules[MAX_RULES][MAX_RULE_LENGTH];

    printf("Enter the number of rules: ");
    scanf("%d", &rule_count);
    getchar();  // Consume newline character left by scanf

    if (rule_count > MAX_RULES) {
        printf("Rule count exceeds maximum limit.\n");
        return 1;
    }

    printf("Enter the rules (one per line):\n");
    for (int i = 0; i < rule_count; i++) {
        fgets(rules[i], sizeof(rules[i]), stdin);
        // Remove newline character
        rules[i][strcspn(rules[i], "\n")] = '\0';
    }

    printf("\nOriginal Grammar:\n");
    for (int i = 0; i < rule_count; i++) {
        printf("%s\n", rules[i]);
    }

    printf("\nEliminated Left Recursion Grammar:\n");
    eliminate_left_recursion(rules, rule_count);

    return 0;
}

// Function to eliminate left recursion
void eliminate_left_recursion(char rules[MAX_RULES][MAX_RULE_LENGTH], int rule_count) {
    for (int i = 0; i < rule_count; i++) {
        char rule[MAX_RULE_LENGTH];
        char non_terminal[MAX_RULE_LENGTH];
        char rest_of_rule[MAX_RULE_LENGTH];
        char new_rule[MAX_RULE_LENGTH];
        char alpha[MAX_RULE_LENGTH];
        char beta[MAX_RULE_LENGTH];
        char *ptr;

        // Copy the rule to avoid modifying the original
        strcpy(rule, rules[i]);

        // Extract the non-terminal and the rest of the rule
        char *arrow_pos = strchr(rule, '>');
        if (arrow_pos == NULL) {
            continue;
        }
        *arrow_pos = '\0';
        strcpy(non_terminal, rule);
        rest_of_rule[0] = '\0';
        strcpy(rest_of_rule, arrow_pos + 1);

        // Trim leading and trailing spaces
        ptr = rest_of_rule;
        while (isspace(*ptr)) ptr++;
        char *end = ptr + strlen(ptr) - 1;
        while (end > ptr && isspace(*end)) end--;
        *(end + 1) = '\0';

        // Check for left recursion
        if (strncmp(ptr, non_terminal, strlen(non_terminal)) == 0) {
            // Direct left recursion
            printf("%s -> %s A'\n", non_terminal, ptr + strlen(non_terminal));

            // Create new rules
            snprintf(alpha, sizeof(alpha), "%s", ptr + strlen(non_terminal));
            printf("%s' -> %s %s' | e\n", non_terminal, alpha, non_terminal);
        } else {
            // No left recursion detected, just print the original rule
            printf("%s -> %s\n", non_terminal, ptr);
        }
    }
}
