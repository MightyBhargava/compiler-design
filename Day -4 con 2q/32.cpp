#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_RULE_LENGTH 100

void left_factoring(char rules[MAX_RULES][MAX_RULE_LENGTH], int rule_count);

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

    printf("\nLeft Factored Grammar:\n");
    left_factoring(rules, rule_count);

    return 0;
}

// Function to perform left factoring
void left_factoring(char rules[MAX_RULES][MAX_RULE_LENGTH], int rule_count) {
    for (int i = 0; i < rule_count; i++) {
        char rule[MAX_RULE_LENGTH];
        char non_terminal[MAX_RULE_LENGTH];
        char productions[MAX_RULE_LENGTH];
        char new_rule[MAX_RULE_LENGTH];
        char *ptr;

        // Copy the rule to avoid modifying the original
        strcpy(rule, rules[i]);

        // Extract the non-terminal and the productions
        char *arrow_pos = strchr(rule, '>');
        if (arrow_pos == NULL) {
            continue;
        }
        *arrow_pos = '\0';
        strcpy(non_terminal, rule);
        productions[0] = '\0';
        strcpy(productions, arrow_pos + 1);

        // Split productions by '|'
        char *prod = strtok(productions, "|");
        char prefix[MAX_RULE_LENGTH] = "";
        char suffix[MAX_RULE_LENGTH] = "";
        int has_common_prefix = 0;

        while (prod != NULL) {
            // Remove leading and trailing spaces
            ptr = prod;
            while (isspace(*ptr)) ptr++;
            char *end = ptr + strlen(ptr) - 1;
            while (end > ptr && isspace(*end)) end--;
            *(end + 1) = '\0';

            // Find common prefix
            if (strlen(prefix) == 0) {
                strcpy(prefix, ptr);
            } else {
                int common_length = 0;
                for (int j = 0; ptr[j] && prefix[j] && ptr[j] == prefix[j]; j++) {
                    common_length++;
                }
                if (common_length > 0) {
                    has_common_prefix = 1;
                    strncpy(suffix, prefix + common_length, sizeof(suffix) - 1);
                    suffix[sizeof(suffix) - 1] = '\0';
                    strncpy(prefix, ptr, common_length);
                    prefix[common_length] = '\0';
                } else {
                    // No common prefix
                    printf("%s -> %s | %s\n", non_terminal, prefix, ptr);
                    prefix[0] = '\0';
                }
            }
            prod = strtok(NULL, "|");
        }

        if (has_common_prefix) {
            // Print left-factored rule
            printf("%s -> %s %s'\n", non_terminal, prefix, non_terminal);
            printf("%s' -> %s | %s\n", non_terminal, suffix, prefix);
        }
    }
}
