#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of keywords
char *keywords[] = {
    "int", "float", "char", "double", "if", "else", 
    "while", "for", "return", "void", "main"
};

// List of operators
char operators[] = {'+', '-', '*', '/', '=', '<', '>', '!', '&', '|'};

// Function to check if a string is a keyword
int isKeyword(char *word) {
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    int numOperators = sizeof(operators) / sizeof(operators[0]);
    for (int i = 0; i < numOperators; i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to analyze the input file
void analyze(FILE *file) {
    char ch;
    char buffer[100];
    int bufferIndex = 0;
    
    while ((ch = fgetc(file)) != EOF) {
        // Skip whitespace and newlines
        if (isspace(ch) || ch == '\n') {
            continue;
        }
        
        // Check for operators
        if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
            continue;
        }
        
        // Check for identifiers or keywords
        if (isalpha(ch) || ch == '_') {
            bufferIndex = 0;
            buffer[bufferIndex++] = ch;
            
            while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
                buffer[bufferIndex++] = ch;
            }
            buffer[bufferIndex] = '\0';
            
            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
            
            // Put back the non-alphanumeric character
            ungetc(ch, file);
        }
        
        // Check for numbers (optional)
        else if (isdigit(ch)) {
            bufferIndex = 0;
            buffer[bufferIndex++] = ch;
            
            while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
                buffer[bufferIndex++] = ch;
            }
            buffer[bufferIndex] = '\0';
            
            printf("Number: %s\n", buffer);
            
            // Put back the non-digit character
            ungetc(ch, file);
        }
    }
}

int main() {
    char filename[100];
    FILE *file;
    
    printf("Enter the input file name: ");
    scanf("%s", filename);
    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    printf("\nLexical Analysis Results:\n");
    printf("------------------------\n");
    analyze(file);
    
    fclose(file);
    return 0;
}