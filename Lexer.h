#include <string>
#include <iostream>
#include <vector>
#ifndef LEXER_H
#define LEXER_H

enum TokenType {
    // Keywords
    LET, PRINT,

    // Identifiers and literals
    IDENTIFIER, NUMBER,

    // Operators
    PLUS, MINUS, STAR, SLASH, CARET, EQUAL,

    // Symbols
    LPAREN, RPAREN, SEMICOLON, COMMA,

    // End of file
    END
};

struct Token {
    TokenType type;
    std::string value;

    Token(const TokenType &t, const std::string &v)
        : type{ t }, value{ v } { }
};

std::string tokenTypeToString(const TokenType &t) {
    switch(t) {
        case NUMBER: return "NUMBERS";
        case IDENTIFIER: return "IDENTIFIER";
        case EQUAL: return "EQUALS";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case STAR: return "STAR";
        case SLASH: return "SLASH";
        case CARET: return "CARET";
        case SEMICOLON: return "SEMICOLON";
        case COMMA: return "COMMA";
        case LET: return "LET";
        case PRINT: return "PRINT";
        case END: return "END";
        default: return "UNKNOWN";
    }
}

/* Class for the Lexer */
class Lexer
{
private:
    std::string input;
    size_t pos = 0;

    char peek() { return pos < input.size() ? input[pos] : '\0'; }
    char get() { return pos < input.size() ? input[pos++] : '\0'; }
    void skipWhitespace() {
        while (isspace(peek())) get();
    }

public:
    class InvalidCharacter {
    private:
        char ch;
    public:
        InvalidCharacter(char c) : ch{ c } { }
        std::string what() const {
            return ("Error during lexical analysis: Invalid character " + std::string(1, ch) + '\n');
        }
    };

public:
    Lexer(const std::string &s) : input{ s } { }

    /* Method to get the next token in the source program */
    Token getNextToken() {
        skipWhitespace();

        // Token a number literal.
        if (isdigit(peek())) {
            std::string num;
            while (isdigit(peek()) || peek() == '.') num += get();
            return Token(NUMBER, num);
        }

        // Token a keyword or an identifier, which starts with a letter.
        if (isalpha(peek())) {
            std::string name;
            while (isalnum(peek())) name += get();
            // Check if the identifier is the same as keywords.
            if (name == "let") return Token(LET, name);
            if (name == "print") return Token(PRINT, name);
            else return Token(IDENTIFIER, name);
        }

        // Check for other token types.
        char ch = get();
        switch (ch) {
            case '+':   return Token(PLUS, "+");
            case '-':   return Token(MINUS, "-");
            case '*':   return Token(STAR, "*");
            case '/':   return Token(SLASH, "/");
            case '^':   return Token(CARET, "^");
            case '(':   return Token(LPAREN, "(");
            case ')':   return Token(RPAREN, ")");
            case '=':   return Token(EQUAL, "=");
            case ';':   return Token(SEMICOLON, ";");
            case ',':   return Token(COMMA, ",");
            case '\0':   return Token(END, "");
        }

        // Otherwise, throw an InvalidCharacter exception.
        throw InvalidCharacter(ch);
    }

    /* The method to return a vector of tokens in the source program */
    std::vector<Token> tokenize() {
        try
        {
            std::vector<Token> tokens;
            while (true) {
                Token t = getNextToken();
                tokens.push_back(t);
                if (t.type == END) break;
            }
            return tokens;
        }
        catch (const InvalidCharacter &e)
        {
            throw e;
        }
    }

    /* The method to print tokens in the source program for demonstration */
    void displayTokens() {
        try
        {
            while (true)
            {
                Token t = getNextToken();
                std::cout << "[ Type: " << tokenTypeToString(t.type)
                          << ", Value: " << t.value << " ]" << std::endl;
                if (t.type == END) break;
            }
        }
        catch(const InvalidCharacter& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};
#endif