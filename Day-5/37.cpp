#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure to hold intermediate code statements
typedef struct Instruction {
    char *result;
    char *op1;
    char operator;
    char *op2;
    struct Instruction *next;
} Instruction;

// Function prototypes
Instruction* createInstruction(const char *result, const char *op1, char operator, const char *op2);
void printInstructions(Instruction *head);
void parseExpression(const char *expr, Instruction **head);

int main() {
    // Example input expression
    const char *expression = "a = b + c * d - e / f";
    Instruction *instructions = NULL;

    // Parse the expression and generate TAC
    parseExpression(expression, &instructions);

    // Print the generated TAC
    printInstructions(instructions);

    // Free memory
    Instruction *temp;
    while (instructions) {
        temp = instructions;
        instructions = instructions->next;
        free(temp->result);
        free(temp->op1);
        free(temp->op2);
        free(temp);
    }

    return 0;
}

// Function to create a new intermediate code instruction
Instruction* createInstruction(const char *result, const char *op1, char operator, const char *op2) {
    Instruction *newInstruction = (Instruction *)malloc(sizeof(Instruction));
    newInstruction->result = strdup(result);
    newInstruction->op1 = strdup(op1);
    newInstruction->operator = operator;
    newInstruction->op2 = strdup(op2);
    newInstruction->next = NULL;
    return newInstruction;
}

// Function to print the list of intermediate code instructions
void printInstructions(Instruction *head) {
    Instruction *current = head;
    while (current) {
        if (current->operator) {
            printf("%s = %s %c %s\n", current->result, current->op1, current->operator, current->op2);
        } else {
            printf("%s = %s\n", current->result, current->op1);
        }
        current = current->next;
    }
}

// Function to parse the expression and generate intermediate code
void parseExpression(const char *expr, Instruction **head) {
    char *tokens = strdup(expr);
    char *token = strtok(tokens, " ");
    char *result = NULL;
    char *op1 = NULL;
    char *op2 = NULL;
    char operator = 0;
    char tempVar[10];
    int tempCount = 1;

    while (token) {
        if (strcmp(token, "=") == 0) {
            result = strtok(NULL, " ");
        } else if (strchr("+-*/", token[0])) {
            operator = token[0];
            op2 = strtok(NULL, " ");
            
            // Create a temporary variable
            snprintf(tempVar, sizeof(tempVar), "t%d", tempCount++);
            
            // Create and add new intermediate code instruction
            Instruction *newInstruction = createInstruction(tempVar, op1, operator, op2);
            newInstruction->next = *head;
            *head = newInstruction;
            
            // Update op1 to the temporary variable
            op1 = strdup(tempVar);
        } else {
            if (op1 == NULL) {
                op1 = token;
            } else {
                op1 = strdup(token);
            }
        }
        token = strtok(NULL, " ");
    }

    // Create final assignment to result
    if (result && op1) {
        Instruction *finalInstruction = createInstruction(result, op1, 0, NULL);
        finalInstruction->next = *head;
        *head = finalInstruction;
    }

    free(tokens);
}
