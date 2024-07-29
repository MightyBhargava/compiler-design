#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Symbol {
    char *name;
    int value;
    struct Symbol *next;
} Symbol;

typedef struct SymbolTable {
    Symbol *table[TABLE_SIZE];
} SymbolTable;

// Hash function
unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}

// Initialize the symbol table
SymbolTable* createSymbolTable() {
    SymbolTable *symTable = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (symTable == NULL) {
        perror("Failed to create symbol table");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        symTable->table[i] = NULL;
    }
    return symTable;
}

// Create a new symbol
Symbol* createSymbol(const char *name, int value) {
    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    if (newSymbol == NULL) {
        perror("Failed to create symbol");
        exit(EXIT_FAILURE);
    }
    newSymbol->name = strdup(name);
    newSymbol->value = value;
    newSymbol->next = NULL;
    return newSymbol;
}

// Insert a symbol into the symbol table
void insertSymbol(SymbolTable *symTable, const char *name, int value) {
    unsigned int index = hash(name);
    Symbol *newSymbol = createSymbol(name, value);
    newSymbol->next = symTable->table[index];
    symTable->table[index] = newSymbol;
}

// Lookup a symbol in the symbol table
Symbol* lookupSymbol(SymbolTable *symTable, const char *name) {
    unsigned int index = hash(name);
    Symbol *current = symTable->table[index];
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Delete a symbol from the symbol table
void deleteSymbol(SymbolTable *symTable, const char *name) {
    unsigned int index = hash(name);
    Symbol *current = symTable->table[index];
    Symbol *prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                symTable->table[index] = current->next;
            }
            free(current->name);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Print the symbol table (for debugging)
void printSymbolTable(SymbolTable *symTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *current = symTable->table[i];
        if (current) {
            printf("Index %d:\n", i);
            while (current) {
                printf("  %s = %d\n", current->name, current->value);
                current = current->next;
            }
        }
    }
}

int main() {
    SymbolTable *symTable = createSymbolTable();

    insertSymbol(symTable, "x", 10);
    insertSymbol(symTable, "y", 20);
    insertSymbol(symTable, "z", 30);

    printf("Symbol table after insertion:\n");
    printSymbolTable(symTable);

    Symbol *sym = lookupSymbol(symTable, "y");
    if (sym) {
        printf("\nFound symbol: %s = %d\n", sym->name, sym->value);
    } else {
        printf("\nSymbol not found\n");
    }

    deleteSymbol(symTable, "y");
    printf("\nSymbol table after deletion:\n");
    printSymbolTable(symTable);

    // Free memory
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *current = symTable->table[i];
        while (current) {
            Symbol *toDelete = current;
            current = current->next;
            free(toDelete->name);
            free(toDelete);
        }
    }
    free(symTable);

    return 0;
}
