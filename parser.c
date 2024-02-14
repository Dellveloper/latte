#include <stdio.h>
#include "lexer.h" // Assume your lexer code is in 'lexer.h'

int currentToken;

// Get the next token from the lexer
void nextToken() {
    currentToken = getNextToken();
}

// Helper functions for better error reporting
void error(const char *msg) {
    printf("Parser error: %s\n", msg);
    exit(1);
}

void match(int expectedToken) {
    if (currentToken == expectedToken) {
        nextToken();
    } else {
        error("Unexpected token");
    }
}

// --- Grammar Productions ---

int primary() {
    switch (currentToken) {
        case TOK_NUMBER: 
            int value = /* Get number value from lexer */; 
            nextToken();
            return value;  
        case TOK_LPAREN:
            nextToken();
            int result = expr();
            match(TOK_RPAREN);
            return result;
        default:
            error("Expected number or '('");
            return 0; // For error recovery
    }
}

int factor() {
    int result = primary();
    while (currentToken == TOK_MUL || currentToken == TOK_DIV) {
        if (currentToken == TOK_MUL) {
            nextToken();
            result *= factor();
        } else if (currentToken == TOK_DIV) {
            nextToken();
            result /= factor();
        }
    }
    return result;
}

int term() {
    int result = factor();
    while (currentToken == TOK_PLUS || currentToken == TOK_MINUS) {
        if (currentToken == TOK_PLUS) {
            nextToken();
            result += term();
        } else if (currentToken == TOK_MINUS) {
            nextToken();
            result -= term();
        }
    }
    return result;
}

int expr() {
    int result = term();
    return result; // For now, only simple expressions
}

// -- Very rudimentary statement parsing --

void statement() {
    switch (currentToken) {
        case TOK_IDENTIFIER: 
            // ... handle variable assignment (needs a symbol table)
            nextToken();
            break;
        case TOK_IF: 
            // ... handle simple if statement (very limited)
            nextToken();
            break;
        // ... add more statement types
        default: 
            error("Expected statement");
    }
}

// Top-level parsing function
void parse() {
    nextToken(); // Fetch the first token
    while (currentToken != TOK_EOF) {
        statement();
    }
}

int main() {
    parse();
    return 0;
}
