#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent an expression
typedef struct Expression {
    char *expr;          // Original expression
    char *tempVar;       // Temporary variable (for optimization)
    struct Expression *next;
} Expression;

// Function prototypes
void addExpression(Expression **head, const char *expr);
void printOptimizedCode(Expression *head);
void optimizeExpressions(Expression *head);
void readExpressionsFromFile(const char *filename, Expression **head);

// Main function
int main() {
    Expression *expressions = NULL;

    // Set the input file name here
    const char *filename = "39.txt";  // Ensure this file is in the same directory as the executable
    
    // Read expressions from the file
    readExpressionsFromFile(filename, &expressions);

    // Optimize the list of expressions
    optimizeExpressions(expressions);

    // Print the optimized code
    printOptimizedCode(expressions);

    // Free memory
    Expression *temp;
    while (expressions) {
        temp = expressions;
        expressions = expressions->next;
        free(temp->expr);
        free(temp->tempVar);
        free(temp);
    }

    return 0;
}

// Function to add an expression to the list
void addExpression(Expression **head, const char *expr) {
    Expression *newExpr = (Expression *)malloc(sizeof(Expression));
    newExpr->expr = strdup(expr);
    newExpr->tempVar = NULL;
    newExpr->next = *head;
    *head = newExpr;
}

// Function to print the optimized code
void printOptimizedCode(Expression *head) {
    printf("Optimized Code:\n");
    Expression *current = head;
    while (current) {
        if (current->tempVar) {
            printf("%s = %s\n", current->tempVar, current->expr);
        } else {
            printf("%s\n", current->expr);
        }
        current = current->next;
    }
}

// Function to optimize expressions by eliminating common subexpressions
void optimizeExpressions(Expression *head) {
    Expression *outer, *inner;
    Expression *commonExprs = NULL;
    int tempCount = 0;

    // Iterate over each expression
    outer = head;
    while (outer) {
        inner = head;
        // Check if the expression has already been encountered
        while (inner != outer) {
            if (strcmp(inner->expr, outer->expr) == 0) {
                // Reuse the existing temporary variable
                if (!inner->tempVar) {
                    inner->tempVar = (char *)malloc(10);
                    sprintf(inner->tempVar, "t%d", tempCount++);
                }
                if (!outer->tempVar) {
                    outer->tempVar = strdup(inner->tempVar);
                }
                break;
            }
            inner = inner->next;
        }
        outer = outer->next;
    }
}

// Function to read expressions from a file and add them to the list
void readExpressionsFromFile(const char *filename, Expression **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove trailing newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
        addExpression(head, buffer);
    }

    fclose(file);
}
