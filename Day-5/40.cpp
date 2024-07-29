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
void printThreeAddressCode(Expression *head);
void generateThreeAddressCode(Expression *head);
void processExpressions();

// Main function
int main() {
    processExpressions();
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

// Function to print the three-address code
void printThreeAddressCode(Expression *head) {
    printf("Three-Address Code:\n");
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

// Function to generate three-address code (simple example)
void generateThreeAddressCode(Expression *head) {
    Expression *current = head;
    int tempCount = 0;

    while (current) {
        // Generate a temporary variable for each unique expression
        if (!current->tempVar) {
            // Assign a new temporary variable name
            current->tempVar = (char *)malloc(10);
            sprintf(current->tempVar, "t%d", tempCount++);
        }
        current = current->next;
    }
}

// Function to process predefined expressions
void processExpressions() {
    Expression *expressions = NULL;

    // Predefined expressions
    addExpression(&expressions, "a = b + c");
    addExpression(&expressions, "d = a * e");
    addExpression(&expressions, "f = d - g");
    
    // Generate three-address code
    generateThreeAddressCode(expressions);

    // Print the three-address code
    printThreeAddressCode(expressions);

    // Free memory
    Expression *temp;
    while (expressions) {
        temp = expressions;
        expressions = expressions->next;
        free(temp->expr);
        free(temp->tempVar);
        free(temp);
    }
}
