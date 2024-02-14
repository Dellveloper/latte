#include <stdio.h>
#include <ctype.h>
#include <string.h>

enum TokenType {
    TOK_EOF,
    TOK_IDENTIFIER,
    TOK_NUMBER,
    TOK_PLUS, 
    TOK_MINUS,
    TOK_MUL,
    TOK_DIV,
    TOK_LPAREN,
    TOK_RPAREN,
    // ... You can add more tokens as your language grows
};

// Simplified list of keywords (a real language has better mechanisms)
char *Keywords[] = { "let", "if", "else", "while", "return" /* ...  */ };
const int NumKeywords = sizeof(Keywords) / sizeof(Keywords[0]);

// Global to track current character
int currentChar = ' ';

// Helper function to consume the current character and fetch the next
void nextChar() {
    currentChar = getchar();
}

// Handles keywords and identifiers
int getIdentifierToken() {
    char identifierStr[100]; // Limit identifier length (improve this!)
    int index = 0;

    while (isalnum(currentChar) || currentChar == '_') {
        identifierStr[index++] = currentChar;
        nextChar();
    }
    identifierStr[index] = '\0';

    // Check if it's a keyword 
    for (int i = 0; i < NumKeywords; i++) {
        if (strcmp(identifierStr, Keywords[i]) == 0) {
            return i + 1; // Assign unique token IDs to keywords 
                           // (offset by 1 since 0 is TOK_EOF)
        }
    }

    return TOK_IDENTIFIER;
}

// Handles integer numbers 
int getNumberToken() {
    int num = 0;
    while (isdigit(currentChar)) {
        num = num * 10 + (currentChar - '0'); 
        nextChar();
    }
    return TOK_NUMBER;
}

// The core lexer function
int getNextToken() {
    // Skip whitespace
    while (isspace(currentChar)) {
        nextChar();
    }

    if (isalpha(currentChar)) {  
        return getIdentifierToken();
    } else if (isdigit(currentChar)) { 
        return getNumberToken();
    }

    switch (currentChar) {
        case '+': nextChar(); return TOK_PLUS;
        case '-': nextChar(); return TOK_MINUS;
        case '*': nextChar(); return TOK_MUL;
        case '/': nextChar(); return TOK_DIV;
        case '(': nextChar(); return TOK_LPAREN;
        case ')': nextChar(); return TOK_RPAREN;
        case EOF: return TOK_EOF;
        default:  nextChar(); return -1;  // Indicate an error
    }
}
